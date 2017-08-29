#include "Customs/PreMenuScene.hpp"
#include "Customs/SdlLogoScript.hpp"
#include "Customs/UnbLogoScript.hpp"
#include "Customs/ZebraLogoScript.hpp"
#include "Customs/ControleLogoScript.hpp"

void PreMenuScene::OnActivation() {
    CreateLogoSdl();
    CreateLogoUnb();
    CreateLogoControle();
    CreateLogoZebra();

}

void  PreMenuScene::OnDeactivation() {}

void  PreMenuScene::OnShown() {}

void  PreMenuScene::OnHidden() {}


void PreMenuScene::CreateLogoSdl(){

    auto sdl_Logo = new GameObject("SDL LOGO", new Vector(0,0),1024,800,1);
    // Renderer
    auto sdl_logoscript = new SdlLogoScript(sdl_Logo);

    AddGameObject(sdl_Logo);



}

void PreMenuScene::CreateLogoUnb(){

    auto unb_Logo = new GameObject("UNB LOGO", new Vector(0,0),1024,800,1);
    // Renderer
    auto unb_logoscript = new UnbLogoScript(unb_Logo);

    AddGameObject(unb_Logo);

}
void PreMenuScene::CreateLogoControle(){

    auto controle_Logo = new GameObject("CONTROLE     LOGO", new Vector(0,0),1024,800,1);
    // Renderer
    auto controle_logoscript = new ControleLogoScript(controle_Logo);

    AddGameObject(controle_Logo);

}
void PreMenuScene::CreateLogoZebra(){

    auto zebra_Logo = new GameObject("ZEBRA LOGO", new Vector(0,0),1024,800,1);
    // Renderer
    auto zebra_logoscript = new ZebraLogoScript(zebra_Logo);

    AddGameObject(zebra_Logo);

}
