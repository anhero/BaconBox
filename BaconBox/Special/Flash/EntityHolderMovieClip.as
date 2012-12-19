package {
import flash.display.MovieClip;

public class EntityHolderMovieClip  extends MovieClip {
	private var _entity:MovieClipEntity;
    public function EntityHolderMovieClip() {
    	super();
    	_entity = MovieClipEntity.create(this);
    }

    public function get entity():MovieClipEntity {
        return _entity;
    }

    public function set entity(value:MovieClipEntity):void {
        _entity = value;
    }
}
}
