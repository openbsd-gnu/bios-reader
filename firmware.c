#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DMIDECODE_PATH "/usr/sbin/dmidecode"

// Function to execute a command and print its output
void execute_and_print(const char *command, const char *label) {
    FILE *fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to execute command: %s\n", command);
        return;
    }

    char buffer[256];
    printf("%s:\n", label);
    while (fgets(buffer, sizeof(buffer), fp)) {
        printf("  %s", buffer);
    }
    pclose(fp);
}

int main() {
    printf("Checking firmware information...\n");

    // Check if UEFI is present
    FILE *efi_check = fopen("/dev/acpi", "r");
    if (efi_check) {
        printf("This system uses UEFI firmware.\n");
        fclose(efi_check);
    } else {
        printf("This system does not use UEFI (likely using Legacy BIOS).\n");
    }

    // Check if dmidecode is available
    if (access(DMIDECODE_PATH, X_OK) != 0) {
        printf("dmidecode is not installed or not executable. Please install it to retrieve firmware details.\n");
        return 1;
    }

    // Fetch BIOS information using dmidecode
    execute_and_print(DMIDECODE_PATH " -s bios-version", "BIOS Version");
    execute_and_print(DMIDECODE_PATH " -s bios-vendor", "BIOS Vendor");
    execute_and_print(DMIDECODE_PATH " -s bios-release-date", "BIOS Release Date");

    return 0;
}
