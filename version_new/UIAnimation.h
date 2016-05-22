#ifndef UI_ANIMATION_H
#define UI_ANIMATION_H

class Object;

//-- Enum for modes that where should UI object be when its animation ends.
enum AnimationStopEnum {
	STOP_AT_ORIGIN,
	STOP_AT_DESTINATION,
	STOP_AT_PATH
};

//-- Class UIAnimation
class UIAnimation
{
protected:
	//================================================= protected members ==========================================================//
	
	//-- The UI object this animation has effect on.
	Object* object;
	//-- How long this animation lasts in one loop cycle. (in seconds)
	float timeLast;
	//-- Whether this animation should be played in loop.
	bool isLoop;
	//-- Where should the UI object be when animation stops.
	AnimationStopEnum stopAt;

	//-- Has the UI object reaches animation destination.
	bool isReachDest = false;
	//-- Should this animation be over.
	bool isOver = false;

	//-- The Animation attached to this animation.
	//-- If not nullptr, attached animation should have effect when this animation ends.
	UIAnimation* attach = nullptr;

	//-- Callback function upon this animation ends
	void (*onStop)();

	//================================================= protected virtual functions ====================================================//
	
	//-- How to interpolates its value from current to destination.
	//-- According to (timeLast) & (destination - origin) & (Time::getInstance()->delta).
	virtual void interpolate() {}
	//-- How to make the UI object return back to original state.
	virtual void mergeToOri() {}
	//-- How to make the UI object jump to destination.
	virtual void mergeToDest() {}
	//-- How to judge whether this animation would go over the destination in the next frame.
	virtual bool overDest() { return true; }

public:
	//=============================================== Constructors & Destructor ======================================================//
	//-- Consructor.
	UIAnimation(Object* object, float timeLast, bool isLoop, AnimationStopEnum stopAt);
	//-- Destructor.
	~UIAnimation();

	//================================================= public functions =============================================================//

	//-- Return whether this animation should be over.
	bool getIsOver();
	//-- Start this animation.
	void start();
	//-- End this animation.
	void end();
	//-- Update function.
	//-- Called in the UI object update().
	//-- Effect between start() & end().
	void update();
	//-- Attach an animation to this animation.
	//-- It would be played when this animation ends.
	void setAttachedAnimation(UIAnimation* anim);
	//-- Start this animation after some delay. (time in seconds)
	void startAfter(float time);
	//-- Set its onStop function
	void setOnStop(void(*onStop)());
};

//-- Class UITransAniamtion
class UITransAnimation : public UIAnimation
{
protected:
	int oriX, oriY;
	int destX, destY;

	float getInterpolateX();
	float getInterpolateY();
	void interpolate() override;
	void mergeToOri() override;
	void mergeToDest() override;
	bool overDest() override;

public:
	UITransAnimation(Object* object, int oriX, int oriY, int destX, int destY, float timeLast, bool isLoop, AnimationStopEnum stopAt);
	
};

//-- Class UIWaitAnimation
class UIWaitAnimation : public UIAnimation
{
protected:

	float timePast = 0;

	float getInterpolation();
	void interpolate() override;
	void mergeToOri() override;
	void mergeToDest() override;
	bool overDest() override;


public:
	UIWaitAnimation(Object* object, float timeLast);
};

//-- Class UIScaleAnimation
class UIScaleAnimation : public UIAnimation
{
protected:
	float oriX, oriY;
	float destX, destY;

	float getInterpolateX();
	float getInterpolateY();

	void interpolate() override;
	void mergeToOri() override;
	void mergeToDest() override;
	bool overDest() override;

public:
	UIScaleAnimation(Object* object, float oriX, float oriY, float destX, float destY, float timeLast, bool isLoop, AnimationStopEnum stopAt);
};

//-- Class UIAlphaAnimation
class UIAlphaAnimation : public UIAnimation
{
protected:
	float oriAlpha;
	float destAlpha;

	float getInterpolation();
	void interpolate() override;
	void mergeToOri() override;
	void mergeToDest() override;
	bool overDest() override;

public:
	UIAlphaAnimation(Object* object, float oriAlpha, float destAlpha, float timeLast, bool isLoop, AnimationStopEnum stopAt);
};

#endif // ! UI_ANIMATION_H
