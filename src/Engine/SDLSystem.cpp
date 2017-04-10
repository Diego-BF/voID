#include "Engine/SDLSystem.h"

// static variables initialization
SDLSystem *SDLSystem::m_instance = 0;

SDLSystem::SDLSystem()
{
    m_frameCounter = 0;
    m_lastFrameTicks = 0;
}

SDLSystem::~SDLSystem()
{
    m_instance = nullptr;
    m_window = nullptr;
    m_renderer = nullptr;
}

void SDLSystem::Init()
{
    INFO("SDLSystem::Init() initialized");

    if (!(InitSDL() && InitIMG() && InitMixer() && InitTTF()))
    {
        ERROR("SDLSystem::Init() failed.");
        return;
    }

    if (!(CreateWindow() && CreateRenderer()))
    {
        ERROR("SDLSystem::Init() failed.");
        return;
    }

    INFO("SDLSystem::Init() completed");
}

void SDLSystem::Run()
{
    INFO("Starting Run().");

    m_isRunning = true;

    Image *img = new Image("assets/8-Bit_Mario.png", 0, 0, 277, 522);
    Renderer *rend = new Renderer(new Vector(100, 100), img, std::make_pair(500, 522));
    GameObject *go = new GameObject("mario", rend);

    Scene *main = new Scene();
    main->AddGameObject(go);
    SceneManager::GetInstance()->AddScene(std::make_pair("main", main));
    SceneManager::GetInstance()->SetCurrentScene("main");

    while (m_isRunning)
    {
        CalculateFramerate();
        InputSystem::GetInstance()->UpdateStates();

        if (InputSystem::GetInstance()->GetKeyDown(INPUT_ESCAPE))
            m_isRunning = false;

        // std::pair<int,int> pos = InputSystem::GetInstance()->GetMousePosition();
        // std::cout << pos.first << " " << pos.second << std::endl;
        // InputSystem::GetInstance()->GetMouseButtonDown(M_INPUT_LEFT);
        // InputSystem::GetInstance()->GetMouseButtonPressed(M_INPUT_LEFT);
        // InputSystem::GetInstance()->GetMouseButtonUp(M_INPUT_LEFT);

        // all updates but draw are called here
        SceneManager::GetInstance()->Update();

        // clearing front buffer
        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);
        // draw update changing the back buffer
        SceneManager::GetInstance()->DrawUpdate();
        // getting back buffer and sending to front buffer
        SDL_RenderPresent(m_renderer);
    }

    INFO("Ending Run().");
}

void SDLSystem::Shutdown()
{
    INFO("Shutdown() Initialized.")

    // get ticks when it is being shutdown
    m_gameEndTicks = SDL_GetTicks();

    IMG_Quit();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

    INFO("Shutdown completed.")
}

SDLSystem *SDLSystem::GetInstance()
{
    if (!m_instance)
        m_instance = new SDLSystem();
    return m_instance;
}

bool SDLSystem::InitSDL()
{
    INFO("Initializing SDL");

    int init = SDL_Init(SDL_INIT_TIMER | SDL_INIT_AUDIO |
                        SDL_INIT_VIDEO | SDL_INIT_JOYSTICK |
                        SDL_INIT_GAMECONTROLLER | SDL_INIT_EVENTS);

    if (init != 0)
    {
        SDL_ERROR("SDLSystem::InitSDL() failed.");
        return false;
    }

    INFO("SDL Initialized.")
    return true;
}

bool SDLSystem::InitIMG()
{
    INFO("Initializing IMG");

    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    int init = IMG_Init(flags);

    if ((init & flags) != flags)
    {
        SDL_IMG_ERROR("SDLSystem::InitIMG() failed.");
        return false;
    }

    INFO("IMG Initialized.");
    return true;
}

bool SDLSystem::InitMixer()
{
    INFO("Initializing Mixer");

    int init = Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);

    if (init != 0)
    {
        SDL_MIX_ERROR("SDLSystem::InitMixer() failed.");
        return false;
    }

    INFO("Mixer Initialized.");
    return true;
}

bool SDLSystem::InitTTF()
{
    INFO("Initializing TTF");

    int init = TTF_Init();

    if (init != 0)
    {
        SDL_TTF_ERROR("SDLSystem::InitTTF() failed.");
        return false;
    }

    INFO("TTF Initialized.");
    return true;
}

bool SDLSystem::CreateWindow()
{
    INFO("Creating window.");

    m_window = SDL_CreateWindow(EngineGlobals::window_title.c_str(),
                                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                EngineGlobals::screen_width, EngineGlobals::screen_height,
                                SDL_WINDOW_SHOWN);

    if (!m_window)
    {
        SDL_ERROR("SDLSystem::CreateWindow() failed.");
        return false;
    }

    INFO("Created window successfully.");
    return true;
}

bool SDLSystem::CreateRenderer()
{
    INFO("Creating renderer.");

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED |
                                                      SDL_RENDERER_PRESENTVSYNC);

    if (!m_renderer)
    {
        SDL_ERROR("SDLSystem::CreateRenderer() failed.");
        return false;
    }

    INFO("Created renderer successfully.");
    return true;
}

void SDLSystem::CalculateFramerate()
{
    m_currentTicks = SDL_GetTicks();
    if (m_currentTicks - m_lastFrameTicks >= 1000)
    {
        m_framerate = m_frameCounter;
        m_frameCounter = 0;
        m_lastFrameTicks = m_currentTicks;
        INFO("Framerate per second: " << m_framerate);
    }
    m_frameCounter++;
}
