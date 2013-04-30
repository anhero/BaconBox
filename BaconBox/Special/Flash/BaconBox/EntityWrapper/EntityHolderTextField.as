 package BaconBox.EntityWrapper {
import flash.display.MovieClip;
import flash.text.TextField;
public class EntityHolderTextField  extends MovieClip {
	private var _entity:Object = null;
    public function EntityHolderTextField() {
    	super();
    }


	public function get textField():TextField {

		return this.getChildByName("text") as TextField;
	}

    public function get entity():Object {
        return _entity;
    }

    public function set entity(value:Object):void {
        _entity = value;
    }

}
}
