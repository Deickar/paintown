#include "../common/init.h"
#include "../common/timer.h"

#include "util/font.h"
#include "util/pointer.h"
#include "util/stretch-bitmap.h"
#include "util/input/input.h"
#include "util/input/input-manager.h"

#include "util/gui/animation.h"
#include "util/gui/box.h"
#include "util/gui/container.h"
#include "util/gui/context-box.h"
#include "util/gui/coordinate.h"
#include "util/gui/cutscene.h"
#include "util/gui/fadetool.h"
#include "util/gui/keys.h"
#include "util/gui/keyinput.h"
#include "util/gui/keyinput_manager.h"
#include "util/gui/lineedit.h"
#include "util/gui/rectarea.h"
#include "util/gui/popup-box.h"
#include "util/gui/scroll-list.h"
#include "util/gui/select-list.h"
#include "util/gui/tabbed-box.h"
#include "util/gui/timer.h"
#include "util/gui/widget.h"

#include <string>
#include <vector>

using namespace std;
using namespace Gui;

enum Keys{
    Up=0,
    Down,
    Left,
    Right,
    Esc,
    Enter,
};

/*! Gui Component */
class GuiComponent : public ScrollItem{
public:
    GuiComponent(const std::string & name):
    name(name),
    active(false){
    }
    virtual ~GuiComponent(){
    }
    // pure virtual funcs
    virtual void up() = 0;
    virtual void down() = 0;
    virtual void right() = 0;
    virtual void left() = 0;
    virtual void actComponent() = 0;
    virtual void drawComponent(const Graphics::Bitmap & where, const Font & font) = 0;
    
    void draw(int x, int y, const Graphics::Bitmap & where, const Font & font, int distance) const{
        if (active){
            font.printf(x, y, Graphics::makeColor(255, 0, 255), where, name, 0);
        } else {
            font.printf(x, y, Graphics::makeColor(255, 255, 255), where, name, 0);
        }
    }
    int size(const Font & font) const{
        return font.textLength(name.c_str());
    }
    void toggle(){
        active = !active;
    }
protected:
    std::string name;
    bool active;
};

/*! TODO Animation Gui Component */
class TestAnimation : public GuiComponent {
public:
    TestAnimation():
    GuiComponent("Gui::Animation"){
    }
    void up(){
    }
    void down(){
    }
    void right(){
    }
    void left(){
    }
    void actComponent(){
    }
    void drawComponent(const Graphics::Bitmap & where, const Font & font){
        font.printf(320 - font.textLength(name.c_str())/2, 15, Graphics::makeColor(255, 255, 255), where, "%s", 0, name.c_str());
        const std::string info = "TODO - Not Implemented yet";
        font.printf(320 - font.textLength(info.c_str())/2, 240, Graphics::makeColor(255, 255, 255), where, "%s", 0, info.c_str());
    }
protected:
};

/*! Box Gui Component */
class TestBox : public GuiComponent {
public:
    TestBox():
    GuiComponent("Gui::Box"),
    size(Gui::RelativePoint(-.5, -.5), Gui::RelativePoint(.5, .5)){
        box.colors.body = Graphics::makeColor(255, 255, 255);
        box.colors.border = Graphics::makeColor(0, 0, 255);
    }
    void up(){
        size.growVertical(.01);
    }
    void down(){
        size.growVertical(-.01);
    }
    void right(){
        size.growHorizontal(.01);
    }
    void left(){
        size.growHorizontal(-.01);
    }
    void actComponent(){
        box.location.growTo(size);
    }
    void drawComponent(const Graphics::Bitmap & where, const Font & font){
        box.render(where);
        font.printf(320 - font.textLength(name.c_str())/2, 15, Graphics::makeColor(255, 255, 255), where, "%s", 0, name.c_str());
    }
protected:
    Gui::Box box;
    Gui::Coordinate size;
};

/*! TODO ContextBox Gui Component */
class TestContextBox : public GuiComponent {
public:
    TestContextBox():
    GuiComponent("Gui::ContextBox"){
    }
    void up(){
    }
    void down(){
    }
    void right(){
    }
    void left(){
    }
    void actComponent(){
    }
    void drawComponent(const Graphics::Bitmap & where, const Font & font){
        font.printf(320 - font.textLength(name.c_str())/2, 15, Graphics::makeColor(255, 255, 255), where, "%s", 0, name.c_str());
        const std::string info = "TODO - Not Implemented yet";
        font.printf(320 - font.textLength(info.c_str())/2, 240, Graphics::makeColor(255, 255, 255), where, "%s", 0, info.c_str());
    }
protected:
};

/*! TODO Cutscene Gui Component */
class TestCutScene : public GuiComponent {
public:
    TestCutScene():
    GuiComponent("Gui::CutScene"){
    }
    void up(){
    }
    void down(){
    }
    void right(){
    }
    void left(){
    }
    void actComponent(){
    }
    void drawComponent(const Graphics::Bitmap & where, const Font & font){
        font.printf(320 - font.textLength(name.c_str())/2, 15, Graphics::makeColor(255, 255, 255), where, "%s", 0, name.c_str());
        const std::string info = "TODO - Not Implemented yet";
        font.printf(320 - font.textLength(info.c_str())/2, 240, Graphics::makeColor(255, 255, 255), where, "%s", 0, info.c_str());
    }
protected:
};

/*! TODO FadeTool Gui Component */
class TestFadeTool : public GuiComponent {
public:
    TestFadeTool():
    GuiComponent("Gui::FadeTool"),
    time(50),
    bitmap(640, 480){
        bitmap.clear();
        fader.setState(FadeTool::FadeIn);
        fader.setFadeInTime(time);
        fader.setFadeOutTime(time);
    }
    void up(){
        time+=5;
        fader.setFadeInTime(time);
        fader.setFadeOutTime(time);
    }
    void down(){
        time-=5;
        fader.setFadeInTime(time);
        fader.setFadeOutTime(time);
    }
    void right(){
        time+=5;
        fader.setFadeInTime(time);
        fader.setFadeOutTime(time);
    }
    void left(){
        time-=5;
        fader.setFadeInTime(time);
        fader.setFadeOutTime(time);
    }
    void actComponent(){
        fader.act();
        if (fader.getState() == FadeTool::NoFade){
            fader.setState(FadeTool::FadeOut);
        } else if (fader.getState() == FadeTool::EndFade){
            fader.setState(FadeTool::FadeIn);
        }
    }
    void drawComponent(const Graphics::Bitmap & where, const Font & font){
        bitmap.putPixel(rand() % 640, rand() % 480, Graphics::makeColor(rand() % 255, rand() % 255, rand() % 255));
        bitmap.Blit(where);
        font.printf(270, 215, Graphics::makeColor(255, 255, 255), where, "Fade Time: %d", 0, time);
        font.printf(320 - font.textLength(name.c_str())/2, 240, Graphics::makeColor(255, 255, 255), where, "%s", 0, name.c_str());
        fader.draw(where);
    }
protected:
    int time;
    Graphics::Bitmap bitmap;
    Gui::FadeTool fader;
};

/*! TODO LineEdit Gui Component */
class TestLineEdit : public GuiComponent {
public:
    TestLineEdit():
    GuiComponent("Gui::LineEdit"){
    }
    void up(){
    }
    void down(){
    }
    void right(){
    }
    void left(){
    }
    void actComponent(){
    }
    void drawComponent(const Graphics::Bitmap & where, const Font & font){
        font.printf(320 - font.textLength(name.c_str())/2, 15, Graphics::makeColor(255, 255, 255), where, "%s", 0, name.c_str());
        const std::string info = "TODO - Not Implemented yet";
        font.printf(320 - font.textLength(info.c_str())/2, 240, Graphics::makeColor(255, 255, 255), where, "%s", 0, info.c_str());
    }
protected:
};

/*! TODO PopupBox Gui Component */
class TestPopupBox : public GuiComponent {
public:
    TestPopupBox():
    GuiComponent("Gui::PopupBox"){
    }
    void up(){
    }
    void down(){
    }
    void right(){
    }
    void left(){
    }
    void actComponent(){
    }
    void drawComponent(const Graphics::Bitmap & where, const Font & font){
        font.printf(320 - font.textLength(name.c_str())/2, 15, Graphics::makeColor(255, 255, 255), where, "%s", 0, name.c_str());
        const std::string info = "TODO - Not Implemented yet";
        font.printf(320 - font.textLength(info.c_str())/2, 240, Graphics::makeColor(255, 255, 255), where, "%s", 0, info.c_str());
    }
protected:
};

/*! TODO ScrollList Gui Component */
class TestScrollList : public GuiComponent {
public:
    TestScrollList():
    GuiComponent("Gui::ScrollList"){
    }
    void up(){
    }
    void down(){
    }
    void right(){
    }
    void left(){
    }
    void actComponent(){
    }
    void drawComponent(const Graphics::Bitmap & where, const Font & font){
        font.printf(320 - font.textLength(name.c_str())/2, 15, Graphics::makeColor(255, 255, 255), where, "%s", 0, name.c_str());
        const std::string info = "TODO - Not Implemented yet";
        font.printf(320 - font.textLength(info.c_str())/2, 240, Graphics::makeColor(255, 255, 255), where, "%s", 0, info.c_str());
    }
protected:
};

/*! TODO NormalList Gui Component */
class TestNormalList : public GuiComponent {
public:
    TestNormalList():
    GuiComponent("Gui::NormalList"){
    }
    void up(){
    }
    void down(){
    }
    void right(){
    }
    void left(){
    }
    void actComponent(){
    }
    void drawComponent(const Graphics::Bitmap & where, const Font & font){
        font.printf(320 - font.textLength(name.c_str())/2, 15, Graphics::makeColor(255, 255, 255), where, "%s", 0, name.c_str());
        const std::string info = "TODO - Not Implemented yet";
        font.printf(320 - font.textLength(info.c_str())/2, 240, Graphics::makeColor(255, 255, 255), where, "%s", 0, info.c_str());
    }
protected:
};

/*! TODO SimpleSelect Gui Component */
class TestSimpleSelect : public GuiComponent {
public:
    TestSimpleSelect():
    GuiComponent("Gui::SimpleSelect"){
    }
    void up(){
    }
    void down(){
    }
    void right(){
    }
    void left(){
    }
    void actComponent(){
    }
    void drawComponent(const Graphics::Bitmap & where, const Font & font){
        font.printf(320 - font.textLength(name.c_str())/2, 15, Graphics::makeColor(255, 255, 255), where, "%s", 0, name.c_str());
        const std::string info = "TODO - Not Implemented yet";
        font.printf(320 - font.textLength(info.c_str())/2, 240, Graphics::makeColor(255, 255, 255), where, "%s", 0, info.c_str());
    }
protected:
};

/*! TODO GridSelect Gui Component */
class TestGridSelect : public GuiComponent {
public:
    TestGridSelect():
    GuiComponent("Gui::GridSelect"){
    }
    void up(){
    }
    void down(){
    }
    void right(){
    }
    void left(){
    }
    void actComponent(){
    }
    void drawComponent(const Graphics::Bitmap & where, const Font & font){
        font.printf(320 - font.textLength(name.c_str())/2, 15, Graphics::makeColor(255, 255, 255), where, "%s", 0, name.c_str());
        const std::string info = "TODO - Not Implemented yet";
        font.printf(320 - font.textLength(info.c_str())/2, 240, Graphics::makeColor(255, 255, 255), where, "%s", 0, info.c_str());
    }
protected:
};

/*! TODO TabbedBox Gui Component */
class TestTabbedBox : public GuiComponent {
public:
    TestTabbedBox():
    GuiComponent("Gui::TabbedBox"){
    }
    void up(){
    }
    void down(){
    }
    void right(){
    }
    void left(){
    }
    void actComponent(){
    }
    void drawComponent(const Graphics::Bitmap & where, const Font & font){
        font.printf(320 - font.textLength(name.c_str())/2, 15, Graphics::makeColor(255, 255, 255), where, "%s", 0, name.c_str());
        const std::string info = "TODO - Not Implemented yet";
        font.printf(320 - font.textLength(info.c_str())/2, 240, Graphics::makeColor(255, 255, 255), where, "%s", 0, info.c_str());
    }
protected:
};

/*! Gui Handler */
class GuiHandler {
public:
    GuiHandler():
    selected(false){
        // Initialize components and store
        components.push_back(new TestAnimation());
        components.push_back(new TestBox());
        components.push_back(new TestContextBox());
        components.push_back(new TestCutScene());
        components.push_back(new TestFadeTool());
        components.push_back(new TestLineEdit());
        components.push_back(new TestPopupBox());
        components.push_back(new TestScrollList());
        components.push_back(new TestNormalList());
        components.push_back(new TestSimpleSelect());
        components.push_back(new TestGridSelect());
        components.push_back(new TestTabbedBox());
        
        // Set first as active
        components[0].convert<GuiComponent>()->toggle();
        
        // Finally add component list to scroll list
        list.addItems(components);
    }
    ~GuiHandler(){
    }
    
    void up(){
        if (!selected){
            components[list.getCurrentIndex()].convert<GuiComponent>()->toggle();
            list.previous();
            components[list.getCurrentIndex()].convert<GuiComponent>()->toggle();
        } else {
            components[list.getCurrentIndex()].convert<GuiComponent>()->up();
        }
    }
    void down(){
        if (!selected){
            components[list.getCurrentIndex()].convert<GuiComponent>()->toggle();
            list.next();
            components[list.getCurrentIndex()].convert<GuiComponent>()->toggle();
        } else {
            components[list.getCurrentIndex()].convert<GuiComponent>()->down();
        }
    }
    void left(){
        if (!selected){
            components[list.getCurrentIndex()].convert<GuiComponent>()->toggle();
            list.previous();
            components[list.getCurrentIndex()].convert<GuiComponent>()->toggle();
        } else {
            components[list.getCurrentIndex()].convert<GuiComponent>()->left();
        }
    }
    void right(){
        if (!selected){
            components[list.getCurrentIndex()].convert<GuiComponent>()->toggle();
            list.next();
            components[list.getCurrentIndex()].convert<GuiComponent>()->toggle();
        } else {
            components[list.getCurrentIndex()].convert<GuiComponent>()->right();
        }
    }
    
    void act(){
        if (!selected){
            list.act();
        } else {
            components[list.getCurrentIndex()].convert<GuiComponent>()->actComponent();
        }
    }
    void draw(const Graphics::Bitmap & work, const Font & font){
        if (!selected){
            list.render(work, font);
        } else {
            components[list.getCurrentIndex()].convert<GuiComponent>()->drawComponent(work, font);
        }
    }
    
    void enter(){
        if (!selected) {
            selected = true;
        }
    }
    void esc(){
        if (selected){
            selected = false;
        }
    }
    
    bool inComponent(){
        return selected;
    }
    
protected:
    bool selected;
    std::vector<Util::ReferenceCount<Gui::ScrollItem> > components;
    Gui::NormalList list;
};

class Logic: public Util::Logic {
public:
    Logic(InputMap<Keys> & input, GuiHandler & handler):
    is_done(false),
    input(input),
    handler(handler){
    }

    bool is_done;
    InputMap<Keys> & input;
    GuiHandler & handler;
    
    bool done(){
        return is_done;
    }

    void run(){
        vector<InputMap<Keys>::InputEvent> out = InputManager::getEvents(input, InputSource());
        for (vector<InputMap<Keys>::InputEvent>::iterator it = out.begin(); it != out.end(); it++){
            const InputMap<Keys>::InputEvent & event = *it;
            if (event.enabled){
                if (event.out == Esc){
                    if (!handler.inComponent()){
                        is_done = true;
                    } else {
                        handler.esc();
                    }
                }
                if (event.out == Up){
                    handler.up();
                }
                if (event.out == Down){
                    handler.down();
                }
                if (event.out == Left){
                    handler.left();
                }
                if (event.out == Right){
                    handler.right();
                }
                if (event.out == Enter){
                    handler.enter();
                }
            }
        }
        
        handler.act();
    
    }

    double ticks(double system){
        return system;
    }
};

class Draw: public Util::Draw {
public:
    Draw(GuiHandler & handler):
    handler(handler),
    controls("Controls: Up, Down, Left, Right, Enter, Esc"){
    }
    
    GuiHandler & handler;
    std::string controls;

    void draw(const Graphics::Bitmap & buffer){
        buffer.clear();
        handler.draw(buffer, Font::getDefaultFont());
        Font::getDefaultFont().printf(320 - Font::getDefaultFont().textLength(controls.c_str())/2, 460, Graphics::makeColor(255, 255, 255), buffer, "%s", 0, controls.c_str());
        buffer.BlitToScreen();
    }
};

int main(int argc, char ** argv){
    Screen::realInit();
    Common::startTimers();
    
    InputManager manager;
    Graphics::Bitmap screen(Graphics::getScreenBuffer());
    Util::Parameter<Graphics::Bitmap*> use(Graphics::screenParameter, &screen);
    
    InputMap<Keys> input;
    input.set(Keyboard::Key_ESC, 0, true, Esc);
    input.set(Keyboard::Key_ENTER, 0, true, Enter);
    input.set(Keyboard::Key_UP, 0, true, Up);
    input.set(Keyboard::Key_DOWN, 0, true, Down);
    input.set(Keyboard::Key_LEFT, 0, true, Left);
    input.set(Keyboard::Key_RIGHT, 0, true, Right);
    
    GuiHandler handler;
    
    Logic logic(input, handler);
    Draw draw(handler);

    Util::standardLoop(logic, draw);
    
    Screen::realFinish();
    return 0;
}
#ifdef USE_ALLEGRO
END_OF_MAIN()
#endif