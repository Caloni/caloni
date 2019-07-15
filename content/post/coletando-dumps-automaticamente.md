---
date: "2012-05-17"
title: Coletando dumps automaticamente
categories: [ "blog" ]
---
**HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\Windows Error Reporting\LocalDumps** key.

| Value               | Description | Type          | Default value             |
|---------------------|-------------|---------------|---------------------------|
| **DumpFolder**      | [1]         | REG_EXPAND_SZ | %LOCALAPPDATA%\CrashDumps |
| **DumpCount**       | [2]         | REG_DWORD     | 10                        |
| **DumpType**        | [3]         | REG_DWORD     | 1                         |
| **CustomDumpFlags** | [4]         | REG_DWORD     | [5]                       |

 - [1] The path where the dump files are to be stored. If you do not use the default path, then make sure that the folder contains ACLs that allow the crashing process to write data to the folder.For service crashes, the dump is written to service specific profile folders depending on the service account used. For example, the profile folder for System services is %WINDIR%\System32\Config\SystemProfile. For Network and Local Services, the folder is %WINDIR%\ServiceProfiles.
 - [2] The maximum number of dump files in the folder. When the maximum value is exceeded, the oldest dump file in the folder will be replaced with the new dump file.
 - [3] Specify one of the following dump types: 0 = Custom dump, 1 = Mini dump, 2 = Full dump
 - [4] The custom dump options to be used. This value is used only when **DumpType** is set to 0.The options are a bitwise combination of the **MINIDUMP_TYPE** enumeration values.
 - [5] MiniDumpWithDataSegs or MiniDumpWithUnloadedModules or MiniDumpWithProcessThreadData.

Fonte: MSDN (Collecting User-Mode Dumps).
