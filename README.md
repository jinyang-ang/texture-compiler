Texture compiler that converts png and jpegs equivalent into DDS format. It uses GLI for loading and texconv for compression. 
This project focuses on compressing texture maps to be used in custom game engine which may include diffuse,ambient and normal maps etc.
For all compressions other than normal maps, it will compress to BC_3. Normal maps will be compressed to BC_5
