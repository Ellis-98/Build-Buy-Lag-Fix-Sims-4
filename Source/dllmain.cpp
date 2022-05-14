#include "pch.h"
#include <Windows.h>
#include <stdio.h>

#include "NINI.h"

// Ces adresses sont pour le 1.87.40.1030 - utilisées uniquement si le ini n'existe pas ou ne contient pas les entrées respectives.

constexpr long long PATCH_ADDRESS =     0x0140c8083d;
constexpr long long PATCH_EXPECTED =    0xE081C71774;
constexpr long long PATCH_TARGET =      0xE081C717EB;

void Patch()
{
    char
        szText[150];

    unsigned long long
        ullData;

    NINI
        *pNini = new NINI();

    long long
        llAddress = PATCH_ADDRESS,
        llExpected = PATCH_EXPECTED,
        llTarget = PATCH_TARGET;

    bool
        bShowErrors = true,
        bShowWarnings = true,
        bShowSuccess = true,

        bExitAfterPatch = false;

    bool
        bMalformedAddress = false,
        bMalformedExpected = false,
        bMalformedTarget = false;

    // Chargement de l'ini (depuis les scripts ou la racine)

    if (!pNini->Load("BBLagFix.ini"))
        pNini->Load("../BBLagFix.ini");

    if (pNini->IsLoaded()) // Si le fichier a été analysé, chargez les données :
    {
        // Patch

        if (pNini->GetKeyValueByName("Address", szText, sizeof(szText), "Patch") &&
            sscanf_s(szText, "%llx", &llAddress) != 1)
            bMalformedAddress = true;

        if (pNini->GetKeyValueByName("Expected", szText, sizeof(szText), "Patch") &&
            sscanf_s(szText, "%llx", &llExpected) != 1)
            bMalformedExpected = true;

        if (pNini->GetKeyValueByName("Target", szText, sizeof(szText), "Patch") &&
            sscanf_s(szText, "%llx", &llTarget) != 1)
            bMalformedTarget = true;

        // Messages

        pNini->GetKeyValueByName("Errors", bShowErrors, "Messages");
        pNini->GetKeyValueByName("Warnings", bShowWarnings, "Messages");
        pNini->GetKeyValueByName("Success", bShowSuccess, "Messages");

        // Debug

        pNini->GetKeyValueByName("ExitAfterPatch", bExitAfterPatch, "Debug");
    }

    // Vérifie si certaines des données du patch sont invalides et émet une erreur, si cela est possible.

    if (bShowErrors)
    {
        if (bMalformedAddress)
            MessageBoxA(NULL, "ERROR:\nAddress value in configuration file is not a valid hex value.", "BBLagFix", 0);

        if (bMalformedExpected)
            MessageBoxA(NULL, "ERROR:\nExpected value in configuration file is not a valid hex value.", "BBLagFix", 0);

        if (bMalformedTarget)
            MessageBoxA(NULL, "ERROR:\nTarget value in configuration file is not a valid hex value.", "BBLagFix", 0);
    }

    // Deuxième vérification pour le patch lui-même

    if (!bMalformedAddress && !bMalformedExpected && !bMalformedTarget)
    {
        // Obtenir les données actuelles à partir de l'adresse mémoire

        ullData = *(unsigned long long*)llAddress;

        if (ullData != llExpected && ullData != llTarget) // Si les données cibles ne correspondent ni à la valeur attendue, ni à la valeur corrigée, il y a eu un problème.
        {
            if (bShowErrors)
            {
                snprintf(szText, sizeof(szText), "ERROR:\nFailed to apply BBLagFix patch.\nExpected data: %llx\nActual data: %llx\nMake sure to use the correct version.", llExpected, ullData);
                MessageBoxA(NULL, szText, "BBLagFix", 0);
            }
        }
        else if (ullData == llTarget) // Déjà corrigée ?
        {
            if (bShowWarnings)
            {
                MessageBoxA(NULL, "WARNING:\nBBLagFix was already applied.", "BBLagFix", 0);
            }
        }
        else // Patch...
        {
            DWORD
                dwOldProt;

            VirtualProtect((VOID*)llAddress, sizeof(unsigned long long), PAGE_EXECUTE_READWRITE, &dwOldProt);

            *(unsigned long long*)llAddress = (unsigned)llTarget;

            VirtualProtect((VOID*)llAddress, sizeof(unsigned long long), dwOldProt, &dwOldProt);

            if (bShowSuccess)
            {
                MessageBoxA(NULL, "SUCCESS:\nBBLagFix applied successfully.", "BBLagFix", 0);
            }
        }
    }

    // Debug

    if(bExitAfterPatch)
        ExitProcess(0);

    delete pNini;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
    switch (dwReason)
    {
    case DLL_PROCESS_ATTACH:

        Patch();

        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}
