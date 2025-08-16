void win(void)
{
  struct termios termios_p; // [rsp+0h] [rbp-50h] BYREF
  unsigned __int64 v1; // [rsp+48h] [rbp-8h]

  v1 = __readfsqword(0x28u);
  tcgetattr(0, &termios_p);
  termios_p.c_lflag |= 0xAu;
  tcsetattr(0, 0, &termios_p);
  execl("/bin/sh", "sh", 0LL);
  perror("execl failed");
  exit(1);
}

void App::App(App *this)
{
  char v1[8]; // [rsp+10h] [rbp-20h] BYREF
  unsigned __int64 v2; // [rsp+18h] [rbp-18h]

  v2 = __readfsqword(0x28u);
  AppState::AppState(this);
  std::unique_ptr<PostListScreen,std::default_delete<PostListScreen>>::unique_ptr<std::default_delete<PostListScreen>,void>((char *)this + 280);
  std::unique_ptr<PostDetailScreen,std::default_delete<PostDetailScreen>>::unique_ptr<std::default_delete<PostDetailScreen>,void>((char *)this + 288);
  std::unique_ptr<PostCreateScreen,std::default_delete<PostCreateScreen>>::unique_ptr<std::default_delete<PostCreateScreen>,void>((char *)this + 296);
  std::unique_ptr<SettingsScreen,std::default_delete<SettingsScreen>>::unique_ptr<std::default_delete<SettingsScreen>,void>((char *)this + 304);
  std::make_unique<PostListScreen,AppState &>(v1, this);
  std::unique_ptr<PostListScreen,std::default_delete<PostListScreen>>::operator=((char *)this + 280, v1);
  std::unique_ptr<PostListScreen,std::default_delete<PostListScreen>>::~unique_ptr(v1);
  std::make_unique<PostDetailScreen,AppState &>(v1, this);
  std::unique_ptr<PostDetailScreen,std::default_delete<PostDetailScreen>>::operator=((char *)this + 288, v1);
  std::unique_ptr<PostDetailScreen,std::default_delete<PostDetailScreen>>::~unique_ptr(v1);
  std::make_unique<PostCreateScreen,AppState &>(v1, this);
  std::unique_ptr<PostCreateScreen,std::default_delete<PostCreateScreen>>::operator=((char *)this + 296, v1);
  std::unique_ptr<PostCreateScreen,std::default_delete<PostCreateScreen>>::~unique_ptr(v1);
  std::make_unique<SettingsScreen,AppState &>(v1, this);
  std::unique_ptr<SettingsScreen,std::default_delete<SettingsScreen>>::operator=((char *)this + 304, v1);
  std::unique_ptr<SettingsScreen,std::default_delete<SettingsScreen>>::~unique_ptr(v1);
}

unsigned __int64 __fastcall App::run(App *this)
{
  char v2[16]; // [rsp+10h] [rbp-230h] BYREF
  char v3[16]; // [rsp+20h] [rbp-220h] BYREF
  char v4[16]; // [rsp+30h] [rbp-210h] BYREF
  char v5[16]; // [rsp+40h] [rbp-200h] BYREF
  __int64 v6[4]; // [rsp+50h] [rbp-1F0h] BYREF
  char v7[32]; // [rsp+70h] [rbp-1D0h] BYREF
  char v8[32]; // [rsp+90h] [rbp-1B0h] BYREF
  char v9[376]; // [rsp+B0h] [rbp-190h] BYREF
  unsigned __int64 v10; // [rsp+228h] [rbp-18h]

  v10 = __readfsqword(0x28u);
  App::createMainComponent((App *)v2);
  ftxui::ScreenInteractive::Fullscreen((ftxui::ScreenInteractive *)v9);
  v6[0] = (__int64)this;
  v6[1] = (__int64)v9;
  v6[2] = (__int64)v2;
  std::function<std::shared_ptr<ftxui::Node> ()(void)>::function<App::run(void)::{lambda(void)#1},void>(v8, v6);
  std::shared_ptr<ftxui::ComponentBase>::shared_ptr(v5, v2);
  ftxui::Renderer(v3, v5, v8);
  std::shared_ptr<ftxui::ComponentBase>::~shared_ptr(v5);
  std::function<std::shared_ptr<ftxui::Node> ()(void)>::~function(v8);
  std::shared_ptr<ftxui::ComponentBase>::shared_ptr(v4, v2);
  std::function<bool ()(ftxui::Event)>::function<App::run(void)::{lambda(ftxui::Event)#1},void>(v7, v4);
  ftxui::CatchEvent(v8, v7);
  std::shared_ptr<ftxui::ComponentBase>::shared_ptr(v5, v3);
  ftxui::operator|(v6, v5, v8);
  std::shared_ptr<ftxui::ComponentBase>::operator=(v3, v6);
  std::shared_ptr<ftxui::ComponentBase>::~shared_ptr(v6);
  std::shared_ptr<ftxui::ComponentBase>::~shared_ptr(v5);
  std::function<std::shared_ptr<ftxui::ComponentBase> ()(std::shared_ptr<ftxui::ComponentBase>)>::~function(v8);
  std::function<bool ()(ftxui::Event)>::~function(v7);
  App::run(void)::{lambda(ftxui::Event)#1}::~Event(v4);
  std::shared_ptr<ftxui::ComponentBase>::shared_ptr(v6, v3);
  ftxui::ScreenInteractive::Loop(v9, v6);
  std::shared_ptr<ftxui::ComponentBase>::~shared_ptr(v6);
  std::shared_ptr<ftxui::ComponentBase>::~shared_ptr(v3);
  ftxui::ScreenInteractive::~ScreenInteractive((ftxui::ScreenInteractive *)v9);
  std::shared_ptr<ftxui::ComponentBase>::~shared_ptr(v2);
  return v10 - __readfsqword(0x28u);
}

int main(int argc, const char **argv, const char **envp)
{
  char v4[312]; // [rsp+0h] [rbp-150h] BYREF
  unsigned __int64 v5; // [rsp+138h] [rbp-18h]

  v5 = __readfsqword(0x28u);
  App::App((App *)v4);
  App::run((App *)v4);
  App::~App((App *)v4);
  return 0;
}