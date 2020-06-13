---
categories: [ "blog" ]
date: "2010-04-10"
tags: [ "draft", "tools", "english" ]
title: "Using TodoList and Microsoft Project together"
---
The next article about bits is still in the oven. Taking vacation (40 days) had drop me out of ideas! At the moment, I can explain the tips and tricks using  TodoList to manage my team and synchronize my tasks in a Microsoft Project timesheet.

The reasons why I am using TodoList are kind of obvious: it does everything I need to organize my day to day tasks and it is portable. Meanwhile, the Project, besides not being portable (I need to carry on with me a 200 MB installer? And do install?) it uses a hard to change format and it was made to project the world, and not to be easily shared.

So, let's go. Everything we need is a current edition of TodoList and Microsoft Project. The first thing we must to do é to export the tasks we want to a default CSV, using the columns we would like to import to Project:

After that it comes the tricky thing, but not so much. We open the project to where we want to import the tasks and choose the option Open again, but this time we select our friend exported-tasks.CSV.

Before we do import, we got to create a new column  that will keep the TodoList tasks IDs, to make sure that in the next imports we make we could merge datum together. So, create this column using a significant name.

Now we can go on the import process. Imagining to be the first one, let's create a inicial map for this migration:

The time we choose who is who in the columns list, we just need to setup which columns in Project are the counterpart for the columns in TodoList, and remember to allocate our special column ID.

Just more a few Nexts and voilà! We got our tasks properly imported.

But of course all this work would be useless if we had to (sigh) open the Project. To avoid this impure job, we keep on updating the project status in our tiny, tidy TodoList and, when we need, we just import the data again, but this time using a already saved map (follow the screenshots above) and setting our TodoList ID as the key. This way the tasks already present will be just updated, and the unknown tasks will be added. That's the most important trick in this post.

After I researched all this, I just found out the Project won't be necessary anymore. Lucky me. Now, if you don't have such luck, you can use this post =)

