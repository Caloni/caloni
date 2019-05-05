@echo off
if "%2"=="" goto usage
hugo new %1/%2.md
gvim content\%1\%2.md
goto :eof

:usage
echo How to use: new [category] [slug]
echo Categories: (without the .md)
dir /b archetypes
