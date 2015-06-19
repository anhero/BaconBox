package BaconBox.kernel {

import com.adobe.flascc.kernel.PlayerKernel;
import com.adobe.flascc.CModule;
import com.adobe.flascc.vfs.FileHandle;

/**
 * Implements fixes over the default PlayerKernel.
 */
public class BBKernel extends PlayerKernel {
    public function BBKernel() {}

    /**
     * Flushes the VFS to sync the file.
     */
    override public function fsync(fd:int, errnoPtr:int):int {
        if (!CModule.vfs.isValidFileDescriptor(fd)) {
            CModule.write32(errnoPtr, KernelConstants.EBADF)
            return -1
        }
        else {
            var fh:FileHandle = CModule.vfs.getFileHandleFromFileDescriptor(fd);
            fh.backingStore.flush();
        }
        return 0
    }
}

}
