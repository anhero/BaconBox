 package BaconBox {
import flash.display.MovieClip;
import flash.text.TextField;
 import BaconBox.TextEntity;
public class EntityHolderTextField  extends MovieClip {
	private var _entity:TextEntity;
	private var _textId:String = "";
	private var _customFontID:String = "";
    public function EntityHolderTextField() {
    	super();
    	_entity = TextEntity.create();
        _entity.setMovieClip(this);
    }


	public function get textField():TextField {

		return this.getChildByName("text") as TextField;
	}

	[Inspectable(defaultValue="")]
	public function get customFontID():String {
		return _customFontID;
	}

	public function set customFontID(text:String):void {
		_customFontID = text;
	}

	[Inspectable(defaultValue="")]
	public function get textId():String {
		return _textId;
	}

	public function set textId(textId:String):void {
		_textId = textId;
	}

    public function get entity():TextEntity {
        return _entity;
    }

    public function set entity(value:TextEntity):void {
        _entity = value;
    }

}
}
