package BaconBox.EntityWrapper {
import flash.display.MovieClip;
public class EntityHolderMovieClip  extends MovieClip {
	private var _entity:Object = null;
    public function EntityHolderMovieClip() {
    	super();
        gotoAndStop(1);
    }

    public function get entity():Object {
        return _entity;
    }

    public function set entity(value:Object):void {
        _entity = value;
    }

}
}
