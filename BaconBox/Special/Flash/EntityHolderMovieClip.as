package {
import flash.display.MovieClip;

public class EntityHolderMovieClip  extends MovieClip {
	private var _entity:MovieClipEntity;
    private var _bob:int;
    public function EntityHolderMovieClip() {
    	super();
    	_entity = MovieClipEntity.create(this);
        //_bob = 3;
    }
    public function tick():void{
        _entity.tick();
    }

    public function getChiffre():int{
        return 3;
    }
}
}
