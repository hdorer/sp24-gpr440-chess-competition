
#define SDL_MAIN_HANDLED true
#include <algorithm>
#include <iostream>

#include "SDL_image.h"
#include "SDL_surface.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_sdlrenderer.h"
#include <SDL.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#ifdef __EMSCRIPTEN__
EM_JS(int, canvas_get_width, (), { return canvas.width; });

EM_JS(int, canvas_get_height, (), { return canvas.height; });
#endif

#include "chess-simulator.h"
#include "chess.hpp"

#include "PieceSvg.h"
#include "magic_enum/magic_enum.hpp"
#include <chrono>
#include <map>

enum class SimulationState {
  PAUSED,
  RUNNING,
};

// ui settings
auto simulationState = SimulationState::PAUSED;
std::chrono::nanoseconds timeSpentOnMoves = std::chrono::nanoseconds::zero();
std::chrono::nanoseconds timeSpentLastMove = std::chrono::milliseconds::zero();
string gameResult;
vector<string> moves;

void reset(chess::Board &board) {
  board = chess::Board();
  simulationState = SimulationState::PAUSED;
  timeSpentOnMoves = std::chrono::nanoseconds::zero();
  timeSpentLastMove = std::chrono::milliseconds::zero();
  gameResult = "";
  moves.clear();
}

void move(chess::Board &board) {
  if (board.isHalfMoveDraw()) {
    auto result = board.getHalfMoveDrawType();
    gameResult = std::string(magic_enum::enum_name(result.second)) + " " +
                 std::string(magic_enum::enum_name(result.first));
    return;
  }
  auto result = board.isGameOver();
  if (result.second != chess::GameResult::NONE ||
      result.first != chess::GameResultReason::NONE) {
    gameResult = std::string(magic_enum::enum_name(result.second)) + " " +
                 std::string(magic_enum::enum_name(result.first));
    simulationState = SimulationState::PAUSED;
    return;
  }

  std::string turn(magic_enum::enum_name(board.sideToMove().internal()));
  // get stats
  auto beforeTime = std::chrono::high_resolution_clock::now();

  // run!
  auto moveStr = ChessSimulator::Move(board.getFen(true));
  // get stats
  auto afterTime = std::chrono::high_resolution_clock::now();
  // apply move
  auto move = chess::uci::uciToMove(board, moveStr);
  board.makeMove(move);

  // update stats
  timeSpentOnMoves += afterTime - beforeTime;
  timeSpentLastMove = afterTime - beforeTime;
  moves.push_back(std::to_string(board.fullMoveNumber()) + " " + turn + ": " +
                  moveStr);
}

struct Texture {
  SDL_Texture *texture;
  SDL_Surface *surface;
  ~Texture() {
    if (texture)
      SDL_DestroyTexture(texture);
    if (surface)
      SDL_FreeSurface(surface);
  }
};

Texture *SvgStringToTexture(std::string svgString, SDL_Renderer *renderer) {
  Texture *tex = new Texture();
  SDL_RWops *rw = SDL_RWFromConstMem(svgString.c_str(), svgString.size());
  // todo: check if it is correct
  tex->surface = IMG_Load_RW(rw, 1);
  tex->texture = SDL_CreateTextureFromSurface(renderer, tex->surface);

  return tex;
}
auto loadPiecesTextures(SDL_Renderer *renderer) {
  std::map<char, Texture *> map;

  map['P'] = SvgStringToTexture(PawnWhiteSvgString, renderer);
  map['p'] = SvgStringToTexture(PawnBlackSvgString, renderer);
  map['R'] = SvgStringToTexture(RookWhiteSvgString, renderer);
  map['r'] = SvgStringToTexture(RookBlackSvgString, renderer);
  map['N'] = SvgStringToTexture(KnightWhiteSvgString, renderer);
  map['n'] = SvgStringToTexture(KnightBlackSvgString, renderer);
  map['B'] = SvgStringToTexture(BishopWhiteSvgString, renderer);
  map['b'] = SvgStringToTexture(BishopBlackSvgString, renderer);
  map['Q'] = SvgStringToTexture(QueenWhiteSvgString, renderer);
  map['q'] = SvgStringToTexture(QueenBlackSvgString, renderer);
  map['K'] = SvgStringToTexture(KingWhiteSvgString, renderer);
  map['k'] = SvgStringToTexture(KingBlackSvgString, renderer);

  return map;
}

int main(int argc, char *argv[]) {
  // Unused argc, argv
  (void)argc;
  (void)argv;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) !=
      0) {
    printf("Error: %s\n", SDL_GetError());
    return -1;
  }

  auto width = 1280;
  auto height = 720;
#ifdef __EMSCRIPTEN__
  width = canvas_get_width();
  height = canvas_get_height();
#endif

  // Setup window
  SDL_WindowFlags window_flags =
      (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  SDL_Window *window = SDL_CreateWindow(
      "Dear ImGui SDL2+SDL_Renderer example", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED, width, height, window_flags);

  if (!window) {
    std::cout << "Window could not be created!" << std::endl
              << "SDL_Error: " << SDL_GetError() << std::endl;
    abort();
  }

  // Setup SDL_Renderer instance
  SDL_Renderer *renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    SDL_Log("Error creating SDL_Renderer!");
    abort();
  }

  auto piecesTextures = loadPiecesTextures(renderer);

  chess::Board board;

  SDL_RendererInfo info;
  SDL_GetRendererInfo(renderer, &info);
  SDL_Log("Current SDL_Renderer: %s", info.name);

  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  (void)io;

  // Setup Dear ImGui style
  ImGui::StyleColorsDark();

  // Setup Platform/Renderer backends
  ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
  ImGui_ImplSDLRenderer_Init(renderer);

  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

  // Main loop
  bool done = false;

  // Event loop
  while (!done) {
    if (simulationState == SimulationState::RUNNING)
      move(board);

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
      ImGui_ImplSDL2_ProcessEvent(&event);
      if (event.type == SDL_QUIT)
        done = true;
      if (event.type == SDL_WINDOWEVENT &&
          event.window.event == SDL_WINDOWEVENT_CLOSE &&
          event.window.windowID == SDL_GetWindowID(window))
        done = true;
    }

    // Start the Dear ImGui frame
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    // ui goes here
    ImGui::Begin("Settings", nullptr);
    ImGui::Text("%.1fms %.0fFPS | AVG: %.2fms %.1fFPS",
                ImGui::GetIO().DeltaTime * 1000,
                1.0f / ImGui::GetIO().DeltaTime,
                1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

    ImGui::Separator();
    if (ImGui::Button("Reset")) {
      simulationState = SimulationState::RUNNING;
      reset(board);
    }
    ImGui::SameLine();
    if (ImGui::Button("Play")) {
      simulationState = SimulationState::RUNNING;
    }
    ImGui::SameLine();
    if (ImGui::Button("Pause")) {
      simulationState = SimulationState::PAUSED;
    }
    ImGui::SameLine();
    if (ImGui::Button("Step")) {
      simulationState = SimulationState::PAUSED;
      move(board);
    }
    ImGui::Separator();
    // statistics
    ImGui::Text("Acc Time spent: %.3fms", timeSpentOnMoves.count() / 1000000.0);
    ImGui::Text("Last move dur:  %.3fms",
                timeSpentLastMove.count() / 1000000.0);

    ImGui::Text("Game result: %s", gameResult.c_str());
    // moves
    ImGui::Separator();
    ImGui::BeginChild("Moves", ImVec2(0, 0), true);
    // print moves in reverse order
    for (auto it = moves.rbegin(); it != moves.rend(); ++it)
      ImGui::Text("%s", it->c_str());
    ImGui::EndChild(); // end child moves
    ImGui::End();      // end settings

    // Rendering
    ImGui::Render();

    SDL_SetRenderDrawColor(
        renderer, (Uint8)(clear_color.x * 255), (Uint8)(clear_color.y * 255),
        (Uint8)(clear_color.z * 255), (Uint8)(clear_color.w * 255));
    SDL_RenderClear(renderer);

    // draw the chess board
    auto displacementX = width / 2.f - std::min(width, height) / 2.f;
    auto displacementY = height / 2.f - std::min(width, height) / 2.f;
    // get window size from SDL
    int screenWidth, screenHeight;
    SDL_GetWindowSize(window, &screenWidth, &screenHeight);
    int minScreenSide = std::min(screenWidth, screenHeight);

    for (int row = 0; row < 8; row++) {
      for (int col = 0; col < 8; col++) {
        SDL_Rect squareRect = {(int)(displacementX + col * minScreenSide / 8.f),
                               (int)(screenHeight - displacementY -
                                     (row + 1) * minScreenSide / 8.f),
                               (int)(minScreenSide / 8.f),
                               (int)(minScreenSide / 8.f)};

        if ((row + col) % 2 == 0) {
          SDL_SetRenderDrawColor(renderer, 0xAA, 0xAA, 0xAA, 0xFF);
          SDL_RenderFillRect(renderer, &squareRect);
        } else {
          SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
          SDL_RenderFillRect(renderer, &squareRect);
        }

        switch (board.at(chess::Square(row * 8 + col)).internal()) {
        case chess::Piece::underlying::WHITEPAWN:
          SDL_RenderCopy(renderer, piecesTextures['P']->texture, nullptr,
                         &squareRect);
          break;
        case chess::Piece::underlying::BLACKPAWN:
          SDL_RenderCopy(renderer, piecesTextures['p']->texture, nullptr,
                         &squareRect);
          break;
        case chess::Piece::underlying::WHITEROOK:
          SDL_RenderCopy(renderer, piecesTextures['R']->texture, nullptr,
                         &squareRect);
          break;
        case chess::Piece::underlying::BLACKROOK:
          SDL_RenderCopy(renderer, piecesTextures['r']->texture, nullptr,
                         &squareRect);
          break;
        case chess::Piece::underlying::WHITEKNIGHT:
          SDL_RenderCopy(renderer, piecesTextures['N']->texture, nullptr,
                         &squareRect);
          break;
        case chess::Piece::underlying::BLACKKNIGHT:
          SDL_RenderCopy(renderer, piecesTextures['n']->texture, nullptr,
                         &squareRect);
          break;
        case chess::Piece::underlying::WHITEBISHOP:
          SDL_RenderCopy(renderer, piecesTextures['B']->texture, nullptr,
                         &squareRect);
          break;
        case chess::Piece::underlying::BLACKBISHOP:
          SDL_RenderCopy(renderer, piecesTextures['b']->texture, nullptr,
                         &squareRect);
          break;
        case chess::Piece::underlying::WHITEQUEEN:
          SDL_RenderCopy(renderer, piecesTextures['Q']->texture, nullptr,
                         &squareRect);
          break;
        case chess::Piece::underlying::BLACKQUEEN:
          SDL_RenderCopy(renderer, piecesTextures['q']->texture, nullptr,
                         &squareRect);
          break;
        case chess::Piece::underlying::WHITEKING:
          SDL_RenderCopy(renderer, piecesTextures['K']->texture, nullptr,
                         &squareRect);
          break;
        case chess::Piece::underlying::BLACKKING:
          SDL_RenderCopy(renderer, piecesTextures['k']->texture, nullptr,
                         &squareRect);
          break;
        default:
          break;
        }
      }
    }

    // present ui on top of your drawings
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
    SDL_RenderPresent(renderer);

    SDL_Delay(0);
  }

  // Cleanup
  ImGui_ImplSDLRenderer_Shutdown();
  ImGui_ImplSDL2_Shutdown();
  ImGui::DestroyContext();

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}