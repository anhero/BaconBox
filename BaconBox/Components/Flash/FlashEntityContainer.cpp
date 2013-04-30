#include "FlashEntityContainer.h"
#include "BaconBox/Core/Entity.h"
#include "BaconBox/Components/ComponentConnection.h"
#include "BaconBox/Helper/Flash/FlashHelper.h"
#include "BaconBox/Console.h"
#include <AS3/AS3.h>
#include <AS3/AS3++.h>

namespace BaconBox {
	
	FlashEntityContainer::FlashEntityContainer() : EntityContainer() {
		initializeConnections();
	}
	
	FlashEntityContainer::FlashEntityContainer(const FlashEntityContainer &src) : EntityContainer(src) {
	}
	
	FlashEntityContainer::~FlashEntityContainer() {
	}

	void FlashEntityContainer::initializeConnections(){
	    this->addConnection(new ComponentConnection<MovieClipHolder>(&this->movieClipHolder));
	}
	
	void FlashEntityContainer::receiveMessage(int senderID, int destID, int message, void *data) {
				this->EntityContainer::receiveMessage(senderID, destID, message, data);
	}
	
	void FlashEntityContainer::addChild(Entity *newChild){
		AS3::local::var childMC = newChild->getComponent<MovieClipHolder>()->getMovieClip();
		AS3::local::var args[1] = {childMC};
		movieClipHolder->callMethod("addChild", 1,args);
	}
	
	void FlashEntityContainer::addChildAt(Entity *newChild, int index){
		AS3::local::var childMC = newChild->getComponent<MovieClipHolder>()->getMovieClip();
		AS3::local::var args[2] = {childMC, AS3::local::internal::new_int(index)};
		movieClipHolder->callMethod("addChildAt", 1, args);
	}
	
	bool FlashEntityContainer::contains(Entity *child) const {
		AS3::local::var childMC = child->getComponent<MovieClipHolder>()->getMovieClip();
		AS3::local::var args[1] = {childMC};
		AS3::local::var result = movieClipHolder->callMethod("contains", 1, args);
		return AS3::local::internal::bool_valueOf(result);
	}
	
	MovieClipEntity *FlashEntityContainer::getChildAt(int index){
		return internalGetChildAt(index);
	}

	const MovieClipEntity *FlashEntityContainer::getChildAt(int index) const{
		return internalGetChildAt(index);
	}
	
	MovieClipEntity *FlashEntityContainer::getChildByName(const std::string &name){
		return internalgetChildByName(name);
	}
	
	const MovieClipEntity *FlashEntityContainer::getChildByName(const std::string &name) const{
		return internalgetChildByName(name);
	}

	MovieClipEntity *FlashEntityContainer::internalgetChildByName(const std::string &name) const{
		AS3::local::var args[1] = {AS3::local::internal::new_String(name.c_str())};
		AS3::local::var result = movieClipHolder->callMethod("getChildByName", 1, args);
		return FlashHelper::getMCEntityFromMC(result);

	}
	MovieClipEntity *FlashEntityContainer::internalGetChildAt(int index) const{
		AS3::local::var args[1] = {AS3::local::internal::new_int(index)};
		AS3::local::var result = movieClipHolder->callMethod("getChildAt", 1, args);
		return FlashHelper::getMCEntityFromMC(result);
	}

	
	
	int FlashEntityContainer::getChildIndex(Entity *child) const{
		AS3::local::var args[1] = {child->getComponent<MovieClipHolder>()->getMovieClip()};
		AS3::local::var index = movieClipHolder->callMethod("getChildIndex", 1, args);
		return AS3::local::internal::int_valueOf(index);
	}
	
	std::vector<MovieClipEntity *> FlashEntityContainer::getObjectsUnderPoint(const Vector2 &point){
		throw "not implemented yet";
	}
	
	std::vector<const MovieClipEntity *> FlashEntityContainer::getObjectsUnderPoint(const Vector2 &point) const{
		throw "not implemented yet";
	}
	
	MovieClipEntity *FlashEntityContainer::removeChild(Entity *child){
		AS3::local::var args[1] = {child->getComponent<MovieClipHolder>()->getMovieClip()};
		movieClipHolder->callMethod("removeChild", 1, args);
	}
	
	MovieClipEntity *FlashEntityContainer::removeChildAt(int index){
		AS3::local::var args[1] = { AS3::local::internal::new_int(index)};
		movieClipHolder->callMethod("removeChild", 1, args);
	}
	
	void FlashEntityContainer::removeChildren(int beginIndex, int endIndex){
		throw "not implemented yet";
	}
	
	void FlashEntityContainer::setChildIndex(Entity *child, int index){
		throw "not implemented yet";
	}
	
	void FlashEntityContainer::swapChildren(Entity *child1, Entity *child2){
		AS3::local::var args[2] = {child1->getComponent<MovieClipHolder>()->getMovieClip(), child2->getComponent<MovieClipHolder>()->getMovieClip()};
		movieClipHolder->callMethod("swapChildren", 1, args);
	}
	
	void FlashEntityContainer::swapChildrenAt(int index1, int index2){
		AS3::local::var args[2] = { AS3::local::internal::new_int(index1),  AS3::local::internal::new_int(index2)};
		movieClipHolder->callMethod("swapChildrenAt", 1, args);
	}
	
	int FlashEntityContainer::getNbChildren() const{
		AS3::local::var result = movieClipHolder->getProperty("numChildren");
		return AS3::local::internal::int_valueOf(result);
	}
	
	MovieClipEntity * FlashEntityContainer::getParent() const{
		AS3::local::var result = movieClipHolder->getProperty("parent");
		return FlashHelper::getMCEntityFromMC(result);
	}

}
