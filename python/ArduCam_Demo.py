import time
import signal
import cv2

from Arducam import *
from ImageConvert import *

exit_ = False
def sigint_handler(signum, frame):
    global exit_
    exit_ = True

signal.signal(signal.SIGINT, sigint_handler)
signal.signal(signal.SIGTERM, sigint_handler)


def display_fps(index):
    display_fps.frame_count += 1

    current = time.time()
    if current - display_fps.start >= 1:
            print("fps: {}".format(display_fps.frame_count))
            display_fps.frame_count = 0
            display_fps.start = current

display_fps.start = time.time()
display_fps.frame_count = 0

if __name__ == "__main__":
    camera = ArducamCamera()

    # if not camera.openCamera("OV9281_MIPI_2Lane_RAW8_1280x800_40fps_new.cfg"):
    if not camera.openCamera("MT9J001/MT9J001_MONO_8b_640x480_27fps.cfg"):
        raise RuntimeError("Failed to open camera.")

    camera.start()

    # camera.setCtrl("setFramerate", 10)
    camera.setCtrl("setExposureTime", 10000)
    camera.setCtrl("setAnalogueGain", 15)

    scale_width = -1
    
    while not exit_:
        ret, data, cfg = camera.read()

        if ret:
            image = convert_image(data, cfg, camera.color_mode)

            if scale_width != -1:
                scale = scale_width/image.shape[1]
                image = cv2.resize(image, None, fx=scale, fy=scale)

            cv2.imshow("Arducam", image)
        else:
            print("timeout")

        key = cv2.waitKey(1)
        if key == ord('q'):
            exit_ = True
        elif key == ord('s'):
            np.array(data, dtype=np.uint8).tofile("image.raw")

        display_fps(0)

    camera.stop()
    camera.closeCamera()

