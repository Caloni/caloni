---
date: "2012-05-17"
categories: [ "code", "draft",  ]
title: "Coletando dumps automaticamente"
---
| Value           | Description | Type        | Default value             |
|-----------------|-------------|-------------|---------------------------|
| DumpFolder      | [1]         | REGEXPANDSZ | %LOCALAPPDATA%\CrashDumps |
| DumpCount       | [2]         | REGDWORD    | 10                        |
| DumpType        | [3]         | REGDWORD    | 1                         |
| CustomDumpFlags | [4]         | REGDWORD    | [5]                       |

Chave: HKEYLOCALMACHINE\SOFTWARE\Microsoft\Windows\Windows Error Reporting\LocalDumps.

 - [1] The path where the dump files are to be stored. If you do not use the default path, then make sure that the folder contains ACLs that allow the crashing process to write data to the folder.For service crashes, the dump is written to service specific profile folders depending on the service account used. For example, the profile folder for System services is %WINDIR%\System32\Config\SystemProfile. For Network and Local Services, the folder is %WINDIR%\ServiceProfiles.
 - [2] The maximum number of dump files in the folder. When the maximum value is exceeded, the oldest dump file in the folder will be replaced with the new dump file.
 - [3] Specify one of the following dump types: 0 = Custom dump, 1 = Mini dump, 2 = Full dump
 - [4] The custom dump options to be used. This value is used only when DumpType is set to 0.The options are a bitwise combination of the MINIDUMP_TYPE enumeration values.
 - [5] MiniDumpWithDataSegs or MiniDumpWithUnloadedModules or MiniDumpWithProcessThreadData.

Fonte: MSDN (Collecting User-Mode Dumps).
