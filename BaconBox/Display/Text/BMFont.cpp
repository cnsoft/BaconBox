#include <fstream>

#include "BaconBox/Display/Text/BMFont.h"
#include "BaconBox/Console.h"
#include <fstream>
#include "BaconBox/Helper/Serialization/XmlSerializer.h"
#include "BaconBox/Helper/ResourcePathHandler.h"
#include "BaconBox/ResourceManager.h"
#include "../TextureInformation.h"
#include "BaconBox/Display/SubTextureInfo.h"
namespace BaconBox {
		BMFont::BMFont():TextureFont(){}
		BMFont::BMFont(const std::string &newName):TextureFont(newName){}
		
		
		
		int BMFont::getKerning(Char32 leftUnicodeValue, Char32 rightUnicodeValue){
		    std::map<std::pair<Char32, Char32>, int>::iterator i =kerningMap.find(std::pair<Char32,Char32>(leftUnicodeValue, rightUnicodeValue));
		    if(i == kerningMap.end()){
			return 0;
		    }
		    return i->second;
		}

		
	
		TextureGlyphInformation * BMFont::getGlyphInformation(Char32 unicodeValue){
		    std::map<int, TextureGlyphInformation*>::iterator i =charsMap.find(unicodeValue);
		    if(i == charsMap.end()){
			return NULL;
		    }
		    return i->second;
		}

	
		void BMFont::setPixelSize(int pixelSize){
		    Console__error("You can't set the pixel size on this font: " << name << ". BMFont are prerendered.");
		}
		
		void BMFont::loadFontFile(const std::string &filename){
		    std::ifstream f;
		     f.open(filename.c_str());
		     char firstChar;
		     f.get(firstChar);
	

		f.seekg(0, std::ios::beg);
		     
		     if(firstChar == 'i'){
			//Text
		     }
		     else if(firstChar == '<'){
			Value font;
			XmlSerializer xmlReader;
			if(xmlReader.readFromStream(f, font)){
			     std::string path = ResourcePathHandler::getPathFromFilename(filename);
			     std::string textureFilename;
			     std::vector<TextureInformation*> textureInfos;
			     if(font["pages"]["page"].isObject()){
				    textureFilename = font["pages"]["page"]["file"].getString();
				    textureFilename.insert((size_t)0, (int)1, (char)'/');
				    textureFilename.insert(0, path);
				    textureInfos.push_back(ResourceManager::loadTexture(font["pages"]["page"]["file"].getString(),textureFilename, ColorFormat::RGBA));
			     }
			     else{
			     //if there is more than one texture for the font.
				Array pages = font["pages"]["page"].getArray();
				for(Array::iterator i = pages.begin(); i != pages.end(); i++){
				    textureFilename = (*i)["file"].getString();
				    textureFilename.insert((size_t)0, (int)1, (char)'/');
				      textureFilename.insert(0, path);
				    textureInfos.push_back(ResourceManager::loadTexture((*i)["file"].getString(),textureFilename, ColorFormat::RGBA));
				}  
			     }
			     
	

				 Value charValue = font["chars"]["char"];
			     if(charValue.isObject()){
				SubTextureInfo * subTex = new SubTextureInfo(textureInfos[charValue["page"].getInt()], Vector2(charValue["x"].getInt(), charValue["y"].getInt()), Vector2(charValue["width"].getInt(), charValue["height"].getInt()));
				charsMap[charValue["id"].getInt()] = new TextureGlyphInformation(Vector2(charValue["xadvance"].getInt(), 0), Vector2(charValue["xoffset"].getInt(), charValue["yoffset"].getInt()), charValue["id"].getInt(), subTex);
			     }
			     else{
				Array chars = charValue.getArray();
				for(Array::iterator i = chars.begin(); i != chars.end(); i++){
					SubTextureInfo * subTex = new SubTextureInfo(textureInfos[(*i)["page"].getInt()], Vector2((*i)["x"].getInt(), (*i)["y"].getInt()), Vector2((*i)["width"].getInt(), (*i)["height"].getInt()));
					charsMap[(*i)["id"].getInt()] = new TextureGlyphInformation(Vector2((*i)["xadvance"].getInt(), 0), Vector2((*i)["xoffset"].getInt(), (*i)["yoffset"].getInt()), (*i)["id"].getInt(), subTex);
				}  
			     }
				 
			    TextureGlyphInformation* textureInfo = new TextureGlyphInformation();
			    textureInfo->charCode = '\n';
			     charsMap[textureInfo->charCode] = textureInfo;
			     
			     Value kerning = font["kernings"]["kerning"];
			     if(kerning.isObject()){
				 kerningMap[std::pair<Char32, Char32>(kerning["first"].getInt(), kerning["second"].getInt())] = kerning["amount"].getInt();
			     }
			     else{
				Array kernings = kerning.getArray();
				for(Array::iterator i = kernings.begin(); i != kernings.end(); i++){
					 kerningMap[std::pair<Char32, Char32>((*i)["first"].getInt(), (*i)["second"].getInt())] = (*i)["amount"].getInt();
				}  
			     }
			     
			     
				lineHeight = font["common"]["lineHeight"].getInt();
				
				pixelSize = font["info"]["size"].getInt();
			     
			}
			else{
			    Console__error("Failed to load a fond : " << filename);
			}
		     }
		     else {
			 //Binary
		     }
		     
		     f.close();

		 
		}


}