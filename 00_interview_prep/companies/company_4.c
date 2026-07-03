
UART driver
==
APSS                                            Secure SS
{FreeRTOS - QURT, CLI, IDLE}                    {FreeRTOS - QURT, CLI, IDLE}
{UART driver - QAPI, Platform, Config, Hal}     {IPC, Hardware semaphore, similar APIs}
{Vote Aggregator - }
{Power Management/DVFS}
{Clock Driver}
{GPIO Drivers}



Secure boot
==
APSS
bootrom {patch points, OTP values, authentication}
Patches {Flash, Shared-SRAM}
SBL (upper layers of boot)



Host
Encrypt the image
Public key shared with the image binary

Burnt image in Flash
Burn the PK-hash to OTP

Device
Verify PK
Decrypt the image






