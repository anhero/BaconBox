////////////////////////////////////////////////////////////////////////////////
//
//  ADOBE SYSTEMS INCORPORATED
//  Copyright 2011 Adobe Systems Incorporated
//  All Rights Reserved.
//
//  NOTICE: Adobe permits you to use, modify, and distribute this file
//  in accordance with the terms of the license agreement accompanying it.
//
////////////////////////////////////////////////////////////////////////////////

package com.adobe.flascc.vfs
{
import flash.display.Loader;
import flash.events.AsyncErrorEvent;
import flash.events.Event;
import flash.events.EventDispatcher;
import flash.events.IOErrorEvent;
import flash.events.ProgressEvent;
import flash.events.SecurityErrorEvent;
import flash.net.URLLoader;
import flash.net.URLLoaderDataFormat;
import flash.net.URLRequest;
import flash.utils.ByteArray;
import flash.utils.Endian;


public class URLLoaderVFS extends InMemoryBackingStore
{
	// The genfs program generates an as file that
	// defines some of the data needed by this script

	private var bytesLoaded:uint
	private var percentComplete:uint
	private var currentLoader:URLLoader
	private var currentVPath:String
	private var currentUrls:Array = []
	private var currentContents:ByteArray
	var urlLoader:URLLoader
	private var vfsFiles:Array;

	public function URLLoaderVFS()
	{


	}


	public function loadManifest(path:String ="./manifest"):void {
		urlLoader = new URLLoader();
		urlLoader.addEventListener(Event.COMPLETE, onManifestLoaded);
		urlLoader.load(new URLRequest(path));
	}


	private function onManifestLoaded(e:Event):void {
//		var lineArray:Array = e.target.data.split(/\n/);
		vfsFiles =  e.target.data.split(/\n/);
		startNewFile();
	}




	private function startNewFile():void{
		if(currentVPath == null)
		{
			var newfile:String = vfsFiles.shift()
			if(newfile == null)
			{
				// All files finished
				this.dispatchEvent(new Event(Event.COMPLETE));
				return
			}

			var paths:Array = newfile.split(" ");
			var filterFunc:Function = function(path:String, index:int, array:Array){return (path != "");};
			paths = paths.filter(filterFunc);

			var realPath:String;
			var calculatedPath:String;
			if(paths.length >1){
				realPath = paths[0];
				calculatedPath = paths[1];
			}
			else{
				realPath = paths[0];
				calculatedPath = realPath;
			}

			currentVPath = calculatedPath;
			currentContents = new ByteArray()
			currentContents.endian = Endian.LITTLE_ENDIAN
			currentContents.position = 0
			currentUrls.length = 0
			currentUrls.push(realPath);
		}

		startNewDownload();
	}

	private function startNewDownload():void
	{
		var url:String = currentUrls.shift()
		if(url == null) {
			// we're done with this file, put it in the VFS
			//currentContents.uncompress()
			addFile(currentVPath, currentContents);

			// start a new file download
			currentVPath = null
			startNewFile()
			return
		}

		currentLoader = new URLLoader(new URLRequest(url));
		currentLoader.dataFormat= URLLoaderDataFormat.BINARY;
		currentLoader.addEventListener(AsyncErrorEvent.ASYNC_ERROR, onError)
		currentLoader.addEventListener(SecurityErrorEvent.SECURITY_ERROR, onError)
		currentLoader.addEventListener(IOErrorEvent.IO_ERROR, onError)
		currentLoader.addEventListener(Event.COMPLETE, onComplete)
		currentLoader.addEventListener(ProgressEvent.PROGRESS, onProgress)
	}

	private function onComplete(e:Event):void
	{
		bytesLoaded += currentLoader.data.length
		currentContents.writeBytes(currentLoader.data)

		//var pe:ProgressEvent = new ProgressEvent(ProgressEvent.PROGRESS)
		//pe.bytesLoaded = bytesLoaded
		//pe.bytesTotal = vfsTotalSize
		//this.dispatchEvent(pe)

		startNewDownload()
	}

	private function onError(e:Event):void
	{
		this.dispatchEvent(e)
	}

	private function onProgress(e:Event):void
	{
		//var pe:ProgressEvent = new ProgressEvent(ProgressEvent.PROGRESS)
		//pe.bytesLoaded = bytesLoaded + e.target.bytesLoaded
		//pe.bytesTotal = vfsTotalSize
		//this.dispatchEvent(pe)
	}
}
}