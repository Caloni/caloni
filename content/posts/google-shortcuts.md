---
date: "2007-07-06"
title: Google shortcuts
categories: [ "blog", "english" ]
---
I love shortcuts. Since my very first years using computers, shortcuts had become my obsession. I research them through the time, collecting them, using them. For a long time I avoid myself from touching the mouse, trainning to remember all keystroke sequences I know.

> I have nothing against using the mouse neither the people that do it. I'm just not very much enthusiastic in using mice. For sometime, I even believed that the cursor pointer was getting me annoyed, so I developed a program to get rid of it from the screen (using a shortcut, of course). But, one more time, I'm not againt its use, and I use it myself sometimes (when I need to).

Until some time ago the web was not so good for shortcut users. So came out Google, plenty of web applications supporting shortcuts and giving me a true reason to use webmail and web RSS reader without pressing constantly the tab key. But there was a lack for its web search engine. Fortunately, there WAS.

Even being in test, I began to use the new keyboard shortcuts in Google search, available in the Google Experimental Search website. Until now there is shortcuts for next result (J), previous result (K), opening the search (O or <Enter>) and putting the cursor in the search box (/). It is just like Gmail and Google Reader. I was so excited with the idea that I changed the Google search plugin inside Firefox by myself. And now I'm going to tell how to do it (note: Windows only).

To put Google search shortcuts inside Firefox probably your search plugin will be in one of these two folder bellow. Try one of them: %programfiles%, Mozilla Firefox, searchplugins or %appdata%, MozillaFirefoxProfiles, *.defaultsearchplugins. The search plugin file has the name google.xml and you can edit it using notepad or another simple text editor. Bellow is the point where you must insert the new line that will get the plugin able to show the shortcuts inside Google.

    <Url type="text/html" method="GET" template="http://www.google.com/search">
    <Param name="q" value="{searchTerms}"/>
    <...>
    <Param name="esrch" value="BetaShortcuts"/> <!-- Google Shortcuts Here -->
    <!-- Dynamic parameters -->
    <...>
    </Url>

That's all. Now you can get all the best: the best search engine with shortcuts. How can we be even more productive?
