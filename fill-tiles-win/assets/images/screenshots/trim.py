from PIL import Image, ImageDraw
import glob
import os


class OutputConfig:
    width = 720
    height = 400
    conner_radius = 60
    input_dir = "temp"


def add_corners(im, rad):
    circle = Image.new('L', (rad * 2, rad * 2), 0)
    draw = ImageDraw.Draw(circle)
    draw.ellipse((0, 0, rad * 2, rad * 2), fill=255)
    alpha = Image.new('L', im.size, 255)
    w, h = im.size
    alpha.paste(circle.crop((0, 0, rad, rad)), (0, 0))
    alpha.paste(circle.crop((0, rad, rad, rad * 2)), (0, h - rad))
    alpha.paste(circle.crop((rad, 0, rad * 2, rad)), (w - rad, 0))
    alpha.paste(circle.crop((rad, rad, rad * 2, rad * 2)), (w - rad, h - rad))
    im.putalpha(alpha)
    return im


def trim_image(path, config: OutputConfig):
    im = Image.open(path)

    center_x = im.width / 2.0
    center_y = im.height / 2.0

    cropped = im.crop((
        center_x - config.width/2, center_y - config.height/2,
        center_x + config.width/2, center_y + config.height/2))

    cropped = add_corners(cropped, config.conner_radius)
    
    cropped.save(os.path.basename(path))



def main():
    config = OutputConfig()

    files = glob.glob(f"./{config.input_dir}/*")
    for file in files:
        print(f"trim: {file}")
        trim_image(file, config)

main()


