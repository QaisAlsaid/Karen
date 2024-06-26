#include "Karen/Core/Log.h"
#include "Karen/Scene/SceneSerializer.h"
#include "pch.h"
#include "AssetManager.h"

#include <pugixml.hpp>

namespace Karen
{
  AssetManager::AssetManager(const char* cfg)
  {
    loadConfig(cfg);
  }

  void AssetManager::reload()
  {
    for(auto iter : m_textures)
    {
      reloadTexture(iter.first);
    }
    for(auto iter : m_scenes)
    {
      reloadScene(iter.first);
    }
  }

  bool AssetManager::loadConfig(const char* cfg)
  {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(cfg ,
    pugi::parse_default | pugi::parse_declaration);
    if (!result)
    {
      KAREN_CORE_ERROR("Parse Error at: {0}, offset: {1}",result.description(), result.offset);
      return false;
    }
    
    auto assets = doc.child("Assets");
    for(auto asset : assets)
    {
      const std::string& type = asset.child_value("Type");
      //TODO: switch on type hash
      if(type == "Texture2D")
      {
        const std::string& name = asset.child_value("Name");
        const std::string& path = asset.child_value("Path");
        if(name.empty()) { KAREN_CORE_ERROR("No Name in Textuer"); return false; }
        if(path.empty()) { KAREN_CORE_ERROR("No Path in Texture: {0}", name); return false; }
        const std::string& flip = asset.child_value("Flip");
        const std::string& filter = asset.child_value("Filter");
        bool bool_flip = flip != "False";
        const auto& gen_tux = Karen::Texture2D::create(path, bool_flip);
        //TODO: filter
        addTexture(name, gen_tux, path);
      }
      else if(type == "Scene")
      {
        const std::string path = asset.child_value("Path");
        const std::string& name = asset.child_value("Name");
        
        if(name.empty()) { KAREN_CORE_ERROR("No Name in Scene"); return false; }
        if(path.empty()) { KAREN_CORE_ERROR("No Path in Scene: {0}", name); return false; }
        
        ARef<Scene> gen_scene;
        gen_scene.reset(new Scene(name));
        addScene(name, gen_scene, path);
      }
      else
      {
        KAREN_CORE_ASSERT(false);
      }
    }
    return true;
  }

  void AssetManager::addScene(const std::string& name, const ARef<Scene>& scene, const std::string& path)
  {
    if(m_scenes.find(name) != m_scenes.end())
      KAREN_CORE_WARN("Scenes must have unique names, name: " + std::string(name) + " is already taken");
    else [[likely]]
    {
      SceneAsset a_scene;
      a_scene.path = path;
      a_scene.scene = scene;
      m_scenes[name] = a_scene;
      KAREN_CORE_ERROR("Scene added name: {0}", name);
    }
  }

  void AssetManager::reloadScene(const std::string& name)
  {
    if(m_scenes.find(name) == m_scenes.end())
      KAREN_CORE_ERROR("Called reloadScene() with unknown scene name: {0}", name);
    else [[likely]]
    {
      auto& a_scene = m_scenes.at(name);
      SceneSerializer ss(a_scene.scene);
      if(!ss.deSerializeText(a_scene.path.c_str()))
        KAREN_CORE_ERROR("Failed to load Scene from Path: {0}", a_scene.path);
    }
  }
  
  void AssetManager::addTexture(const std::string& name, const ARef<Texture2D>& tux, const std::string& path)
  {
    if(m_textures.find(name) != m_textures.end())
      KAREN_CORE_WARN("Textures must have unique names, name:" + std::string(name) + "is already taken");
    else [[likely]]
    {
      Texture2DAsset a_tux;
      a_tux.path = path;
      a_tux.texture = tux;
      m_textures[name] = a_tux;
      KAREN_CORE_ERROR("TUX added name: {0}", name);
    }
  }

  void AssetManager::reloadTexture(const std::string& name)
  {
    if(m_textures.find(name) == m_textures.end())
      KAREN_CORE_ERROR("Called reloadTexture() with unknown texture name: {0}", name);
    else [[likely]]
    {
      m_textures.at(name).texture = Texture2D::create(m_textures.at(name).path);
    }
  }
}
