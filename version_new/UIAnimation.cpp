////////////////////////////////////////////////////////////////////////
//                                                                    //
//   File:               UIAnimation.cpp                              //
//   Class:              class UIAnimation       : base	              //
//                       class UITransAnimation  : preset: Translate  //
//                       class UIWaitAnimation   : preset: Waiting    //
//                       class UIScaleAnimation  : preset: Scale      //
//                       class UIAlphaAnimation  : preset: Opaque     //
//   < Class Declaration >                                            //
//   Description:        UI Animations                                //  
//                                                                    //
////////////////////////////////////////////////////////////////////////

#include "IncludeClass.h"

// ========================================= UI Animation (Base Class) ========================================== //

UIAnimation::UIAnimation(Object* object, float timeLast, bool isLoop, AnimationStopEnum stopAt)
{
	this->object = object;
	this->timeLast = timeLast;
	this->isLoop = isLoop;
	this->stopAt = stopAt;
}

UIAnimation::~UIAnimation()
{
	std::cout << "animation destructed!" << std::endl;
}

void UIAnimation::start()
{
	object->getComponent(UIAnimator)->addAnimation(this);
	object->receivePick = false;
	mergeToOri();
}

void UIAnimation::startAfter(float time)
{
	UIWaitAnimation* wait = new UIWaitAnimation(object, time);
	wait->setAttachedAnimation(this);
	wait->start();
}

void UIAnimation::end()
{
	switch (stopAt)
	{
	case STOP_AT_DESTINATION:
		mergeToDest();
		break;
	case STOP_AT_ORIGIN:
		mergeToOri();
		break;
	case STOP_AT_PATH:
	default:
		break;
	}
	if(onStop)
		onStop();
	if (attach != nullptr)
	{
		attach->start();
		object->getComponent(UIAnimator)->addAnimation(attach);		
	}
	else
	{
		object->receivePick = true;
	}
}

void UIAnimation::update()
{
	if (isOver)
		return;
	if (isReachDest)
	{
		if (isLoop)
		{
			mergeToOri();
			isReachDest = false;
		}
	}
	else if (overDest())
	{
		mergeToDest();
		isReachDest = true;
		if (!isLoop)
		{
			isOver = true;
		}
	}
	else
	{
		interpolate();
	}
}

bool UIAnimation::getIsOver()
{
	return isOver;
}

void UIAnimation::setAttachedAnimation(UIAnimation* anim)
{
	this->attach = anim;
}

//-- Set its onStop function
void UIAnimation::setOnStop(void(*onStop)())
{
	this->onStop = onStop;
}



// ============================================ UI Transform Animation ============================================== //

UITransAnimation::UITransAnimation(Object* object, int oriX, int oriY, int destX, int destY, float timeLast, bool isLoop, AnimationStopEnum stopAt)
	:UIAnimation(object, timeLast, isLoop, stopAt)
{
	this->oriX = oriX;
	this->oriY = oriY;
	this->destX = destX;
	this->destY = destY;
}

float UITransAnimation::getInterpolateX()
{
	return (destX - oriX) / timeLast * TimeManager::getInstance()->delta;
}
float UITransAnimation::getInterpolateY()
{
	return (destY - oriY) / timeLast * TimeManager::getInstance()->delta;
}

void UITransAnimation::interpolate()
{
	object->getComponent(UITransform)->offset += vec2(getInterpolateX(),  getInterpolateY());
}
void UITransAnimation::mergeToOri()
{
	object->getComponent(UITransform)->setOffset(oriX, oriY);
}
void UITransAnimation::mergeToDest()
{
	object->getComponent(UITransform)->setOffset(destX, destY);
}
bool UITransAnimation::overDest()
{
	return	std::abs(object->getComponent(UITransform)->offset.x + getInterpolateX() - oriX) >= std::abs(destX - oriX) &&
		std::abs(object->getComponent(UITransform)->offset.y + getInterpolateY() - oriY) >= std::abs(destY - oriY);
}




// ============================================ UI Wait Animation ============================================== //

UIWaitAnimation::UIWaitAnimation(Object* object, float timeLast)
	: UIAnimation(object, timeLast, false, STOP_AT_DESTINATION)
{

}

float UIWaitAnimation::getInterpolation()
{
	return TimeManager::getInstance()->delta;
}

void UIWaitAnimation::interpolate()
{
	timePast += getInterpolation();
}

void UIWaitAnimation::mergeToOri()
{

}

void UIWaitAnimation::mergeToDest()
{

}

bool UIWaitAnimation::overDest()
{
	return timePast + getInterpolation() >= timeLast;
}



// ============================================ UI Scale Animation ============================================== //

UIScaleAnimation::UIScaleAnimation(Object* object, float oriX, float oriY, float destX, float destY, float timeLast, bool isLoop, AnimationStopEnum stopAt)
	:UIAnimation(object, timeLast, isLoop, stopAt)
{
	this->oriX = oriX;
	this->oriY = oriY;
	this->destX = destX;
	this->destY = destY;
}

float UIScaleAnimation::getInterpolateX()
{
	return (destX - oriX) / timeLast * TimeManager::getInstance()->delta;
}
float UIScaleAnimation::getInterpolateY()
{
	return (destY - oriY) / timeLast * TimeManager::getInstance()->delta;
}

void UIScaleAnimation::interpolate()
{
	object->getComponent(UITransform)->scale += vec2(getInterpolateX(), getInterpolateY());
}
void UIScaleAnimation::mergeToOri()
{
	object->getComponent(UITransform)->setScale(oriX, oriY);
}
void UIScaleAnimation::mergeToDest()
{
	object->getComponent(UITransform)->setScale(destX, destY);
}
bool UIScaleAnimation::overDest()
{
	return	std::abs(object->getComponent(UITransform)->scale.x + getInterpolateX() - oriX) >= std::abs(destX - oriX) &&
		std::abs(object->getComponent(UITransform)->scale.y + getInterpolateY() - oriY) >= std::abs(destY - oriY);
}



// ============================================ UI Alpha Animation ============================================== //

UIAlphaAnimation::UIAlphaAnimation(Object* object, float oriAlpha, float destAlpha, float timeLast, bool isLoop, AnimationStopEnum stopAt)
	:UIAnimation(object, timeLast, isLoop, stopAt)
{
	this->oriAlpha = oriAlpha;
	this->destAlpha = destAlpha;
}

float UIAlphaAnimation::getInterpolation()
{
	return (destAlpha - oriAlpha) / timeLast * TimeManager::getInstance()->delta;
}

void UIAlphaAnimation::interpolate()
{
	object->getComponent(UIImage)->alpha += getInterpolation();
}

void UIAlphaAnimation::mergeToOri()
{
	object->getComponent(UIImage)->alpha = oriAlpha;
}

void UIAlphaAnimation::mergeToDest()
{
	object->getComponent(UIImage)->alpha = destAlpha;
}

bool UIAlphaAnimation::overDest()
{
	return std::abs(object->getComponent(UIImage)->alpha + getInterpolation() - oriAlpha) >= std::abs(destAlpha- oriAlpha);
}



