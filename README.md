# How to get the nice looking code into Confluence


So essentially, what we're doing is having the confluence iframe direct to an html file, which parses through the code file of your choice, and "beautifies" it for confluence. Then, you can have a separate link underneath, which leads to the actual code file, for an easy wget command or file download.


1. Copy the simpleForLoop.html file from this repository. Put it in your repository, which should have your code file in it. Rename the html file to whatever you want. Personally I named the html file the same thing as the code, for clarity. (simpleForLoop.cpp and simpleForLoop.html)

2. Now, go into the html file, and click the edit button. Change the line (#12):
```
fetch('simpleForLoop.cpp')
```
To whatever the name of your code file is.

3. You may have also noticed this entire example is in cpp (C++ code language). If your code language is something else, go to line (#8):
```
<pre><code id="code-block" class="language-cpp"></code></pre>
```
and change "cpp" to whatever language your code is. Some examples:

Python: py

Javascript: js 

C: c

For other languages, refer to this link with all the languages supported: https://prismjs.com/#supported-languages

4. Now, go to confluence. Add an iframe from the plus button at the top, and edit it so that the link reads:
```
https://OWNEROFGITHUBREPO.github.io/REPONAME/FILENAME.html
```
This will add the code to the iframe, but also make it look much nicer to the viewer.

5. To add the link to the code itself (for a wget or a download), add a link to the actual code file:
```
https://OWNEROFGITHUBREPO.github.io/REPONAME/FILENAME.CODELANGUAGE
```

This will allow the users to actually download the file, through a wget or a manual download.




## Optional tutorial: 

### How to get a github repo's files onto the actual web

So the general idea is that you have to pubish your github repository as an actual website, which you can do through github. Then the links to all of your files are simply another "page" in the website.

To do that:
1. Change repository to public

2. Go to settings>pages:

  Change branches to main and root, this will start the website creation process

3. Wait until site goes up (Could take up to 10 minutes or so)

4. Go to the file in your repository you want to iframe.

5. Then click "raw" in the top right

6. This will bring you to a new page, now technically a website page, you can simply copy that link and use it in an iframe

   Ex: This page's link is:
   ```
   https://elliotgobbert.github.io/iFrameTest/README.md
   ```

Notes:

It can take a bit for the website to refresh a file when you've changed it, so give it 15 minutes or so whenever you make a change.


