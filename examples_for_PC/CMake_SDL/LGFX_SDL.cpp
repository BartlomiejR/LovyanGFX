#include <lgfx/v1/platforms/sdl/Panel_sdl.hpp>
#if defined ( SDL_h_ )

int main_func(bool* running);
void setup(void);
void loop(void);

__attribute__((weak))
int main_func(bool* running)
{
  setup();
  do
  {
    loop();
  } while (*running);
  return 0;
}

__attribute__((weak))
int main(int, char**)
{
  /// SDL�̏���
  if (0 != lgfx::Panel_sdl::setup()) { return 1; }

  /// loopThread�̓���p�t���O
  bool running = true;

  /// loopThread���N��
  auto thread = SDL_CreateThread((SDL_ThreadFunction)main_func, "main_func", &running);

  /// �S���̃E�B���h�E��������܂�SDL�̃C�x���g�E�`�揈�����p��
  while (0 == lgfx::Panel_sdl::loop()) {};

  /// main_func���I������
  running = false;
  SDL_WaitThread(thread, nullptr);

  /// SDL���I������
  return lgfx::Panel_sdl::close();
}
#endif
