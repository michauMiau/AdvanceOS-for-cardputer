#include "PasswordVault.h"
#include "MyOS.h"
#include <ArduinoJson.h>
#include <FS.h>
#include <SD.h>
#include "mbedtls/aes.h"
#include "ExtraMenu.h"

// Path and key settings
const char *VAULT_PATH = "/AdvanceOS/Vault/data.bin";

void PasswordVault::Begin()
{
    if (!SD.exists("/AdvanceOS/Vault"))
    {
        SD.mkdir("/AdvanceOS/Vault");
    }

    if (SD.exists(VAULT_PATH))
    {
        String pass = mainOS->AskFromUserForString("Enter Vault Password",false,true);

        if (!LoadVault(pass))
        {
            mainOS->ShowOnScreenMessege("Wrong Password", 1000);
            mainOS->ChangeMenu(new Extra(mainOS));
            return;
        }

        Password = pass;
    }
    else
    {
        Password = mainOS->AskFromUserForString("Create Vault Password",false);

        doc.to<JsonArray>(); // Create an empty array
        SaveVault(Password);
    }
}

// Helper function for AES encryption/decryption
void PasswordVault::encryptDecrypt(uint8_t *input, size_t inputLen, uint8_t *output, String key, bool encrypt)
{
    mbedtls_aes_context aes;
    uint8_t key256[32] = {0};
    // Generate a 32-byte key from the user's password
    memcpy(key256, key.c_str(), min((size_t)key.length(), (size_t)32));

    mbedtls_aes_init(&aes);
    if (encrypt)
    {
        mbedtls_aes_setkey_enc(&aes, key256, 256);
    }
    else
    {
        mbedtls_aes_setkey_dec(&aes, key256, 256);
    }

    // Encrypt in 16-byte blocks (ECB for simplicity, or CBC for higher security)
    for (size_t i = 0; i < inputLen; i += 16)
    {
        mbedtls_aes_crypt_ecb(&aes, encrypt ? MBEDTLS_AES_ENCRYPT : MBEDTLS_AES_DECRYPT, input + i, output + i);
    }
    mbedtls_aes_free(&aes);
}

void PasswordVault::SaveVault(String userPassword)
{
    String jsonString;
    serializeJson(doc, jsonString);
    size_t originalLen = jsonString.length();

    // Calculate Padding
    size_t paddedLen = ((originalLen / 16) + 1) * 16;
    uint8_t *input = (uint8_t *)calloc(paddedLen, 1);
    uint8_t *output = (uint8_t *)malloc(paddedLen);
    memcpy(input, jsonString.c_str(), originalLen);

    encryptDecrypt(input, paddedLen, output, userPassword, true);
    SD.remove(VAULT_PATH);                         // Delete existing file if it exists
    File file = SD.open(VAULT_PATH, FILE_WRITE);   // Create a new clean file
    file.write((uint8_t *)&originalLen, sizeof(size_t)); // Write actual length first!
    file.write(output, paddedLen);
    file.close();

    free(input);
    free(output);
}

bool PasswordVault::LoadVault(String userPassword)
{
    if (!SD.exists(VAULT_PATH))
        return false;

    File file = SD.open(VAULT_PATH, FILE_READ);
    size_t originalLen;
    file.read((uint8_t *)&originalLen, sizeof(size_t)); // Read original length

    size_t encryptedSize = file.size() - sizeof(size_t);
    uint8_t *input = (uint8_t *)malloc(encryptedSize);
    uint8_t *output = (uint8_t *)malloc(encryptedSize);

    file.read(input, encryptedSize);
    file.close();

    encryptDecrypt(input, encryptedSize, output, userPassword, false);

    // Clear and load only up to the original length
    doc.clear();
    // Add null terminator to output to make it a valid string for ArduinoJson
    output[originalLen] = '\0';

    DeserializationError error = deserializeJson(doc, (char *)output);

    free(input);
    free(output);
    return (error == DeserializationError::Ok);
}

void PasswordVault::Loop()
{
    if (mainOS->NewKey.ifKeyJustPress('`'))
    {
        mainOS->ChangeMenu(new Extra(mainOS));
    }
    size_t itemCount = doc.as<JsonArray>().size();

    if (mainOS->NewKey.ifKeyJustPress(';')) 
    {
        if (selectedIndex > 0)
            selectedIndex--;
    }
    if (mainOS->NewKey.ifKeyJustPress('='))
    {
        CreateEntry();
    }
    if (mainOS->NewKey.ifKeyJustPress(KEY_BACKSPACE))
    {
        if (mainOS->AskSomthing("Are You sure You Want To Delete Entry?"))
        {DeleteEntry();}
    }
    if (mainOS->NewKey.ifKeyJustPress('.')) 
    {
        if (selectedIndex < itemCount - 1)
            selectedIndex++;
    }

    if (!mainOS->screenOff)
    {
        Draw();
    }
}

void PasswordVault::Draw()
{
    // Create Sprite
    mainOS->sprite.createSprite(SCREEN_W, SCREEN_H - TopOffset);
    mainOS->sprite.clear(BLACK);
    mainOS->sprite.setTextSize(1);

    JsonArray arr = doc.as<JsonArray>();
    int yPos = 5;
    int lineHeight = 55; // Increased height to accommodate 3 lines + gaps

    // Scrolling calculation: how many items fit on the screen
    int maxVisibleItems = (SCREEN_H - TopOffset) / lineHeight;
    int scrollOffset = 0;
    if (selectedIndex >= maxVisibleItems)
    {
        scrollOffset = selectedIndex - maxVisibleItems + 1;
    }

    if (arr.size() == 0)
    {
        mainOS->sprite.setTextColor(DARKGREY);
        mainOS->sprite.setCursor(10, 10);
        mainOS->sprite.print("No Passwords Found. Press '+' to Add.");
    }
    else
    {
        for (int i = scrollOffset; i < arr.size(); i++)
        {
            // If out of screen bounds, break
            if (yPos + lineHeight > (SCREEN_H - TopOffset))
                break;

            // Get data from JSON
            const char *title = arr[i]["t"] | "No Title";
            const char *user = arr[i]["u"] | "No User";
            const char *pass = arr[i]["p"] | "No Pass";

            // Draw blue background for selected item
            if (i == selectedIndex)
            {
                mainOS->sprite.fillRect(0, yPos - 2, SCREEN_W, lineHeight - 4, BLUE);
                mainOS->sprite.setTextColor(WHITE);
            }
            else
            {
                mainOS->sprite.setTextColor(GREEN);
            }

            // Line 1: Title
            mainOS->sprite.setCursor(10, yPos);
            mainOS->sprite.print(title);

            // Line 2: Username
            if (i != selectedIndex)
                mainOS->sprite.setTextColor(LIGHTGREY);
            mainOS->sprite.setCursor(10, yPos + 15);
            mainOS->sprite.print("Username: ");
            mainOS->sprite.print(user);

            // Line 3: Password
            if (i != selectedIndex)
                mainOS->sprite.setTextColor(YELLOW);
            mainOS->sprite.setCursor(10, yPos + 30);
            mainOS->sprite.print("Password: ");
            mainOS->sprite.print(pass);

            // Horizontal divider line
            mainOS->sprite.drawFastHLine(0, yPos + lineHeight - 6, SCREEN_W, DARKGREY);

            yPos += lineHeight;
        }
    }

    // Draw scrollbar on the right if there are many items
    if (arr.size() > maxVisibleItems)
    {
        int barHeight = (SCREEN_H - TopOffset) / (arr.size() / (float)maxVisibleItems);
        int barPos = (selectedIndex * (SCREEN_H - TopOffset - barHeight)) / (arr.size() - 1);
        mainOS->sprite.fillRect(SCREEN_W - 4, barPos, 3, barHeight, WHITE);
    }

    mainOS->sprite.pushSprite(0, TopOffset);
    mainOS->sprite.deleteSprite();
}

String PasswordVault::AskForPassword()
{
    Password = mainOS->AskFromUserForString("Set Up Password",false);
    return Password;
}

void PasswordVault::CreateEntry()
{
    String title = mainOS->AskFromUserForString("Title",false);
    String user = mainOS->AskFromUserForString("User",false);
    String pass = mainOS->AskFromUserForString("Password",false);

    JsonArray arr = doc.as<JsonArray>();

    JsonObject obj = arr.add<JsonObject>();

    obj["t"] = title;
    obj["u"] = user;
    obj["p"] = pass;

    SaveVault(Password);
}

void PasswordVault::DeleteEntry()
{
    JsonArray arr = doc.as<JsonArray>();
    
    // Check if there are items and index is in range
    if (arr.size() > 0 && selectedIndex < arr.size()) {
        // Remove item from array
        arr.remove(selectedIndex);
        
        // Update index if we deleted the last one
        if (selectedIndex >= arr.size() && selectedIndex > 0) {
            selectedIndex--;
        }

        // Save back to file to persist changes
        SaveVault(Password);
        
        // Optional: Notify user that deletion succeeded
        mainOS->ShowOnScreenMessege("Deleted!", 500);
    }
}