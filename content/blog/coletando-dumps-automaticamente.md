---
date: "2012-05-17"
title: Coletando dumps automaticamente
categories: [ "blog" ]
---
**HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\Windows Error Reporting\LocalDumps** key.

<table cellpadding="0" width="608" cellspacing="0" border="1" >
<tbody >
<tr >

<td width="96" valign="top" >Value
</td>

<td width="209" valign="top" >Description
</td>

<td width="95" valign="top" >Type
</td>

<td width="208" valign="top" >Default value
</td>
</tr>
<tr >

<td width="96" valign="top" >**DumpFolder**
</td>

<td width="209" valign="top" >The path where the dump files are to be stored. If you do not use the default path, then make sure that the folder contains ACLs that allow the crashing process to write data to the folder.For service crashes, the dump is written to service specific profile folders depending on the service account used. For example, the profile folder for System services is %WINDIR%\System32\Config\SystemProfile. For Network and Local Services, the folder is %WINDIR%\ServiceProfiles.
</td>

<td width="95" valign="top" >REG_EXPAND_SZ
</td>

<td width="208" valign="top" >%LOCALAPPDATA%\CrashDumps
</td>
</tr>
<tr >

<td width="96" valign="top" >**DumpCount**
</td>

<td width="209" valign="top" >The maximum number of dump files in the folder. When the maximum value is exceeded, the oldest dump file in the folder will be replaced with the new dump file.
</td>

<td width="95" valign="top" >REG_DWORD
</td>

<td width="208" valign="top" >10
</td>
</tr>
<tr >

<td width="96" valign="top" >**DumpType**
</td>

<td width="209" valign="top" >Specify one of the following dump types:

	
  * 0: Custom dump

	
  * 1: Mini dump

	
  * 2: Full dump

</td>

<td width="95" valign="top" >REG_DWORD
</td>

<td width="208" valign="top" >1
</td>
</tr>
<tr >

<td width="96" valign="top" >**CustomDumpFlags**
</td>

<td width="209" valign="top" >The custom dump options to be used. This value is used only when **DumpType** is set to 0.The options are a bitwise combination of the [**MINIDUMP_TYPE**](http://msdn.microsoft.com/en-us/library/ms680519) enumeration values.
</td>

<td width="95" valign="top" >REG_DWORD
</td>

<td width="208" valign="top" >MiniDumpWithDataSegs | MiniDumpWithUnloadedModules | MiniDumpWithProcessThreadData.
</td>
</tr>
</tbody>
</table>
Isso quer dizer que se:

[![crash-me-build-and-run](http://i.imgur.com/8u4rV7L.png)](/images/11346140275_d325e64ae9_o.png)

Então:

[![crash-me-run-and-dump](http://i.imgur.com/DEYUjLX.png)](/images/11346236114_41457fcc65_o.png)

Fonte: [Collecting User-Mode Dumps (Windows)](http://msdn.microsoft.com/en-us/library/bb787181).

E mais! [WER Settings](http://msdn.microsoft.com/en-us/library/bb513638(VS.85).aspx)
