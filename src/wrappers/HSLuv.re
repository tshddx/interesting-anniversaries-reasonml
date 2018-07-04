[@bs.module "hsluv"]
external hsluvToRgb : ((float, float, float)) => (float, float, float) =
  "hsluvToRgb";

[@bs.module "hsluv"]
external rgbToHsluv : ((float, float, float)) => (float, float, float) =
  "rgbToHsluv";