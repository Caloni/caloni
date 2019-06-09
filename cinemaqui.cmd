@echo off
hugo new cinemaqui/%1.md
hugo new movies/%1.md
gvim content\cinemaqui\%1.md content\movies\%1.md
