[@bs.module "hsluv"]
external hsluvToRgb : ((float, float, float)) => (float, float, float) =
  "hsluvToRgb";

[@bs.module "hsluv"]
external rgbToHsluv : ((float, float, float)) => (float, float, float) =
  "rgbToHsluv";

[@bs.module "hsluv"]
external hpluvToRgb : ((float, float, float)) => (float, float, float) =
  "hpluvToRgb";

[@bs.module "hsluv"]
external rgbToHpluv : ((float, float, float)) => (float, float, float) =
  "rgbToHpluv";