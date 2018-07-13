[@bs.module "chroma"]
external hsluvToRgb : ((float, float, float)) => (float, float, float) =
  "hsluvToRgb";

[@bs.module "chroma"]
external hpluvToRgb : ((float, float, float)) => (float, float, float) =
  "hpluvToRgb";