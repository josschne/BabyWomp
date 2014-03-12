#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using CocosDenshion::SimpleAudioEngine;

USING_NS_CC;

std::vector<std::string> images = 
{
    "1215441305125576364lemmling_Cartoon_giraffe.svg.med.png",
    "12154413311479870315lemmling_Cartoon_gnu.svg.med.png",
    "1215441410235483012lemmling_Cartoon_squirrel.svg.med.png",
    "12154414931495521192lemmling_Cartoon_kangaroo.svg.med.png",
    "12154415151126295659lemmling_Cartoon_owl.svg.med.png",
    "12154415421767612404lemmling_Simple_cartoon_mouse.svg.med.png",
    "12154416611241630675lemmling_Cartoon_penguin.svg.med.png",
    "12161376021593473697lemmling_Cartoon_goat.svg.med.png",
    "1216137669335864135lemmling_Cartoon_beaver.svg.med.png",
    "12161376851595770453lemmling_Cartoon_elephant.svg.med.png",
    "12161396401315330062lemmling_Cartoon_bear.svg.med.png",
    "12161396651491232743lemmling_Cartoon_dog.svg.med.png",
    "12161397191917421375lemmling_Cartoon_cat.svg.med.png",
    "1216139760278927551lemmling_Cartoon_cow.svg.med.png",
    "1216139922123941827lemmling_Cartoon_sheep.svg.med.png",
    "12161399281891548596lemmling_Cartoon_elk.svg.med.png",
    "1216306562167833124lemmling_Cartoon_ghost.svg.med.png",
    "1237098529983464009StudioFibonacci_Cartoon_monkey.svg.med.png",
    "1237098546824050827StudioFibonacci_Cartoon_zebra.svg.med.png",
    "12375620701544626982StudioFibonacci_Cartoon_hippo.svg.med.png",
    "1245696568353635238bloodsong_Chicken-RoundCartoon.svg.med.png",
    "1245696592590661388bloodsong_Pig-RoundCartoon.svg.med.png",
};

std::vector<std::string> sounds = 
{
    "119450__lmbubec__girl-laugh.wav",
    "123897__sempoo__laughter.wav",
    "135387__ashjenx__child-laughing.wav",
    "184616__kim-headlee__young-female-child-laughing.wav",
    "862__memexikon__cacaw.aif",
    "bicycle-horn-1.wav",
    "squeak toy - squeak1.wav",
    "squeak toy - squeak2.wav",
    "squeak toy - squeak3.wav",
    "squeak toy - squeak5.wav",
    "xylophone-1.wav",
    "xylophone-2.wav",
};

bool HelloWorld::touchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    static int i=0;

    SimpleAudioEngine::getInstance()->playEffect(sounds[rand() % sounds.size()].c_str());

    auto sprite = Sprite::create(images[rand() % images.size()]);
    sprite->setPosition(touch->getStartLocation());
    sprite->setGlobalZOrder(i++);
    this->addChild(sprite, 0);

    auto fadeOut = FadeOut::create(3);
    sprite->runAction( Sequence::create(fadeOut, RemoveSelf::create(), NULL) );
    auto zoomIn = ScaleTo::create(3, 2);
    sprite->runAction( zoomIn );

    return true;
}

void HelloWorld::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *event)
{
    static int i=0;
    Size visibleSize = Director::getInstance()->getVisibleSize();

    SimpleAudioEngine::getInstance()->playEffect(sounds[rand() % sounds.size()].c_str());

    auto sprite = Sprite::create(images[rand() % images.size()]);
    sprite->setPosition(Point(rand() % (int)visibleSize.width, rand() % (int)visibleSize.height));
    sprite->setGlobalZOrder(i++);
    this->addChild(sprite, 0);

    auto fadeOut = FadeOut::create(3);
    sprite->runAction( Sequence::create(fadeOut, RemoveSelf::create(), NULL) );
    auto zoomIn = ScaleTo::create(3, 2);
    sprite->runAction( zoomIn );
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(HelloWorld::keyPressed, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    auto touchlistener = EventListenerTouchOneByOne::create();
    touchlistener->onTouchBegan = CC_CALLBACK_2(HelloWorld::touchBegan, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchlistener, this);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    return true;
}


void HelloWorld::menuCloseCallback(Object* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
