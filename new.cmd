@echo off
if "%1"=="" goto usage
hugo new posts/%1.md
gvim content\posts\%1.md
goto :eof

:usage
echo How to use: new [slug]
