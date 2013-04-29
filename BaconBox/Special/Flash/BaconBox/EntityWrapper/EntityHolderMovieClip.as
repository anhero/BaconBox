package BaconBox.EntityWrapper {
import flash.display.MovieClip;
public class EntityHolderMovieClip  extends MovieClip {
	private var _entity:Object;
    public function EntityHolderMovieClip() {
    	super();
    }

    public function get entity():Object {
        return _entity;
    }

    public function set entity(value:Object):void {
        _entity = value;
    }

}
}
