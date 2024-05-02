Put the desired assets to be converted into the assets folder and update the descriptor.json accordingly by adding another section.
Indicate format if it's gamma textured and BC should be set to 3 UNLESS it is a normal map.
Eg.	
{
    "textures": [
      {
        "file_path": "assets/ContentBrowser/pause.png",
        "format": "SRGB",					
        "BC": 3,
        "name": "pause"
      }
    ],
    "folder_name": "pause"
}

Save and click on RUNME.bat and the a output folder will appear with name corresponding to the folder_name specified in the json.
Copy the folder and paste accordingly.