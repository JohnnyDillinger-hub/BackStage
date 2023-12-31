#ifndef GAME_APPLICATION_H
#define GAME_APPLICATION_H

#include "GameState.h"

#include "../Components/ActorFactory.h"
#include "../Components/Actor.h"

#include <memory>
#include <vector>
#include <map>
#include <string>

class GUIContainer;
class EventManager;
class Box2DPhysics;
class TextRenderer;
class AudioEngine;
class IEventData;
class Renderer;
class Scene;

/*
    The (singleton) application class for the game; manages the coupling
    and de-coupling of all game sub-systems and connects their logic.
*/
class GameApplication
{
private:
    // game state
    float m_ScreenWidth, m_ScreenHeight; // the screen width/height in pixels the game runs in
    bool  m_Active;                      // whether the game is currently active
    bool  m_Keys[1024];                  // ASCII keyboard keys currently pressed
    bool  m_KeysPressed[1024];           // ASCII keyboard keys that have been pressed without release
    float m_GameTime;                    // total time in seconds the game has run (reset per level)
    float m_PhysicsTime;                 // separate time counter next to m_GameTime for maintaining consistent physics state

    GameState m_GameState;                                           // current state of the game
    std::map<ActorID, std::shared_ptr<Actor>>     m_Actors;          // a list of all the game's actors/entities
    std::map<std::string, std::shared_ptr<Actor>> m_ImportantActors; // a smaller actor list relating actor names to actors' memory 

    // game-sub systems
    Scene        *m_Scene;        // the game's scene graph and render system
    Renderer     *m_Renderer;     // the game's render-specific logic
    EventManager *m_EventManager; // the game's sub-system communication system
    ActorFactory *m_ActorFactory; // the game's actor generation system
    Box2DPhysics *m_Physics;      // the game's decoupled physics system
    AudioEngine  *m_Audio;        // the game's audio management system
    TextRenderer *m_TextRenderer; // the game's text rendering system

    // GUI
    std::map<std::string, std::shared_ptr<GUIContainer>> m_GUIContainers; // contains all the game's GUI items

    // singleton pattern, constructor private
    static std::shared_ptr<GameApplication> m_Instance;
    GameApplication();
public:
    // retrieves a single instance of this object
    static std::shared_ptr<GameApplication> GetInstance()
    {
        if (!m_Instance)
            m_Instance = std::shared_ptr<GameApplication>(new GameApplication);
        return m_Instance;
    }
    ~GameApplication();

    // initializes the game
    void Initialize(float width, float height);
    // cleans the game; cleans memory
    void CleanUp();
    // generates and returns a new actor/entity of given type
    std::shared_ptr<Actor> CreateActor(DEFAULT_ACTOR_TYPES type);
    // returns an actor given its ID
    std::shared_ptr<Actor> GetActor(ActorID actorID);
    // defines a link between a text keyword and an actor/entity for easy look-up
    void				   SetImportantActor(std::string, std::shared_ptr<Actor> actor);
    // retrieves an actor based on its pre-linked text keyword
    std::shared_ptr<Actor> GetImportantActor(std::string);

    // updates all relevant game sub-systems and logic
    void Update(float deltaTime);
    // renders the game
    void Render();
    // processes a keyboard key pressed in OS-independent fashion
    void ProcessKeyboardDown(short key);
    // processes a keyboard key released in OS-independent fashion 
    void ProcessKeyboardUp(short key);
    // processes mouse movement in OS-independent fashion
    void ProcessMouseMove(float x, float y);
    // processes mouse button clicks in OS-independent fashion
    void ProcessMouseClick(bool leftButton);
    // returns whether a given keyboard character key is pressed
    bool IsKeyPressed(char key, bool check_once = false);

    // switches game state
    void SwitchState(GameState state = GameState::GAME_NONE);

    // returns whether the game is active
    bool                GetActive() { return m_Active; }
    // returns the game's configured screen width
    float               ScreenWidth() { return m_ScreenWidth; }
    // returns the game's configured screen height
    float               ScreenHeight() { return m_ScreenHeight; }
    // returns the game's scene sub-system
    Scene*        const GetScene() { return m_Scene; }
    // returns the game's renderer sub-system
    Renderer*     const GetRenderer() { return m_Renderer; }
    // returns the game's event sub-system
    EventManager* const GetEventManager() { return m_EventManager; }
    // returns the game's physics sub-system
    Box2DPhysics* const GetPhysics() { return m_Physics; }
    // returns the game's text renderer sub-system
    TextRenderer* const GetTextRenderer() { return m_TextRenderer; }
    // returns the game's audio sub-system
    AudioEngine*  const GetAudio() { return m_Audio; }

    // returns the game's running time
	float const GetTime();

    // event logic fires whenever a game level should be loaded/initialized
    void OnStartLevel(std::shared_ptr<IEventData> eventData);
    // event logic fires whenever the game should quit
    void OnQuitGame(std::shared_ptr<IEventData> eventData);
    // event logic fires whenever a game actor is destroyed
    void OnDestroyActor(std::shared_ptr<IEventData> eventData);
};
#endif