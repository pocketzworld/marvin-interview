/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "Isometric.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);


	

    /////////////////////////////
    // 3. add your codes below...

	// auto tilemap = TMXTiledMap::create(nullptr);
	// tilemap->setMapSize(Size(10, 10));

	//size of one unit relative to the ground png
	const auto tileSize = 111 * 1 / sqrt(2);
	const int sizeX = 5;
	const int sizeY = 5;
	int zOrder = sizeX * sizeY;
	for (int y = 0; y < sizeY;y++) {
		for (int x = 0;x < sizeX;x++) {
			
			auto isoSprite = Sprite::create("grass.png");
			// isoSprite->setScale(.5f);
			if (isoSprite == nullptr)
			{
				problemLoading("'grass.png'");
			}
			else
			{
				auto projectedPos = Isometric::project(Vec3(x * tileSize, 0, y * tileSize));
				isoSprite->setPosition(projectedPos);
				isoSprite->setGlobalZOrder(zOrder--);
				this->addChild(isoSprite, 2);				
			}
		}
	}

	//draw some debug info lines
	auto drawNode = DrawNode::create();
	drawNode->drawLine(Isometric::project(Vec3(0, 0, 0)), Isometric::project(Vec3(1 * tileSize, 0, 0)), Color4F::RED);
	drawNode->drawLine(Isometric::project(Vec3(0, 0, 0)), Isometric::project(Vec3(0, 0, 1 * tileSize)), Color4F::BLUE);

	drawNode->setGlobalZOrder(100);
	this->addChild(drawNode,2);
	auto cam = this->getDefaultCamera();
	cam->setPosition(Vec2(0, 0));
	// cam->setScale(0.1f);
	// cam->setPosition3D(Vec3(0, 0, 1));

	
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
