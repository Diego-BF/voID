#include "Engine/GraphicsSystem.hpp"
#include "Engine/SDLSystem.hpp"
#include "Engine/sdl2include.hpp"

#include "Log/log.hpp"

#include <iostream>

GraphicsSystem *GraphicsSystem::m_instance = 0;

GraphicsSystem::GraphicsSystem() {}

GraphicsSystem::~GraphicsSystem() { m_instance = nullptr; }

GraphicsSystem *GraphicsSystem::GetInstance() {
    if (!m_instance) {
        m_instance = new GraphicsSystem();
    }
    return m_instance;
}

void GraphicsSystem::Draw(Image *img, Vector *position,
                          std::pair<int, int> sizes) {
    SDL_Rect dest;
    dest.w = sizes.first;
    dest.h = sizes.second;
    dest.x = position->m_x;
    dest.y = position->m_y;

  /* SDL_SetRenderDrawColor(SDLSystem::GetInstance()->GetRenderer(), 0, 255, 0, 255);
     SDL_RenderDrawRect(SDLSystem::GetInstance()->GetRenderer(), &dest);
     SDL_RenderDrawLine(SDLSystem::GetInstance()->GetRenderer(), 0, 0, dest.x,dest.y);        
  */

    int result;
    result = SDL_RenderCopyEx(SDLSystem::GetInstance()->GetRenderer(),
                            img->GetTexture(), img->GetRect(), &dest,
                            img->GetRotationAngle(), img->GetSDLPivot(),
                            img->GetSDLFlip());

    if (result < 0) {
        ERROR(SDL_GetError());
    }
}

void GraphicsSystem::DrawFrame(Image *img, Frame *frame, Vector *position,int destw,int desth) {
    SDL_Rect dest;
    dest.w = destw;
    dest.h = desth;
    dest.x = position->m_x;
    dest.y = position->m_y;

  /* SDL_SetRenderDrawColor(SDLSystem::GetInstance()->GetRenderer(), 0, 255, 0,255);
     SDL_RenderDrawRect(SDLSystem::GetInstance()->GetRenderer(), &dest);
     SDL_RenderDrawLine(SDLSystem::GetInstance()->GetRenderer(), 0, 0, dest.x,dest.y);
  */

    int result;
    result = SDL_RenderCopyEx(SDLSystem::GetInstance()->GetRenderer(),
                            img->GetTexture(), frame->GetRect(), &dest,
                            img->GetRotationAngle(), img->GetSDLPivot(),
                            img->GetSDLFlip());

    if (result < 0) {
        ERROR(SDL_GetError());
    }
}

void GraphicsSystem::DrawText(SDL_Texture *texture, SDL_Rect *destRect) {
    SDL_RenderCopy(SDLSystem::GetInstance()->GetRenderer(), texture, NULL, destRect);
}

void GraphicsSystem::DrawPoint(Vector point) {
    int result = SDL_RenderDrawPoint(SDLSystem::GetInstance()->GetRenderer(), 
    point.m_x, point.m_y);

    if (result) {
    SDL_ERROR("Drawing point error");
  }
}

void GraphicsSystem::DrawCircle(Vector &center, float radius, Uint8 r, Uint8 g,
                                Uint8 b, Uint8 a) {

    SDL_SetRenderDrawColor(SDLSystem::GetInstance()->GetRenderer(), r, g, b, a);
    Vector point;

    for (int angle = 0; angle < 360; angle++) {
        point.m_x = center.m_x + cos(angle) * radius;
        point.m_y = center.m_y - sin(angle) * radius;
        int result = SDL_RenderDrawPoint(SDLSystem::GetInstance()->GetRenderer(),
                                     point.m_x, point.m_y);
    if (result < 0) {
        ERROR(SDL_GetError());
    }
  }
}

void GraphicsSystem::DrawFillCircle(Vector &center, float radius, Uint8 r,
                                    Uint8 g, Uint8 b, Uint8 a) {

    SDL_SetRenderDrawColor(SDLSystem::GetInstance()->GetRenderer(), r, g, b, a);
    Vector point;

    for (float angle = 0; angle < 360; angle += 0.01) {
        point.m_x = center.m_x + cos(angle) * radius;
        point.m_y = center.m_y - sin(angle) * radius;

        int result = SDL_RenderDrawLine(SDLSystem::GetInstance()->GetRenderer(),
        center.m_x, center.m_y, point.m_x, point.m_y);

    if (result < 0) {
        ERROR(SDL_GetError());
    }
  }
}

void GraphicsSystem::DrawFillRectangle(Vector &position, int width, int height,
                                       Uint8 r, Uint8 g, Uint8 b, Uint8 a) {
  
    SDL_SetRenderDrawColor(SDLSystem::GetInstance()->GetRenderer(), r, g, b, a);

    SDL_Rect rect;
    rect.x = position.m_x;
    rect.y = position.m_y;
    rect.w = width;
    rect.h = height;

    int result = SDL_RenderFillRect(SDLSystem::GetInstance()->GetRenderer(), &rect);

  if (result < 0) {
      ERROR(SDL_GetError());
  }
}

void GraphicsSystem::DrawFillRectangle(SDL_Rect* source, int width, int height,
                                       Uint8 r, Uint8 g, Uint8 b, Uint8 a) {

    SDL_SetRenderDrawColor(SDLSystem::GetInstance()->GetRenderer(), r, g, b, a);

    SDL_Rect rect;
    rect.x = source->x;
    rect.y = source->y;
    rect.w = source->w;
    rect.h = source->h;

    int result = SDL_RenderFillRect(SDLSystem::GetInstance()->GetRenderer(), &rect);

    if (result < 0) {
        ERROR(SDL_GetError());
    }
}
