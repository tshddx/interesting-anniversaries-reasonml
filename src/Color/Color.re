type t = {
  r: float,
  g: float,
  b: float,
};

/* | HSLuv(float, float, float); */
let constrainByte = n => n |> max(0) |> min(255);

let constrainUnit = n => n |> max(0.0) |> min(1.0);

let byteToUnit = byte => (byte |> constrainByte |> float_of_int) /. 255.0;

let unitToByte = unit => {
  let floatByte = (unit |> constrainUnit) *. 255.0;
  floatByte |> Utils.round |> int_of_float;
};

let unitToHexString = unit => unit |> unitToByte |> Printf.sprintf("%02x");

let hexPairToUnit = hexPair =>
  if (hexPair |> String.length == 2) {
    switch (int_of_string({j|0x$hexPair|j})) {
    | int => Some(int |> byteToUnit)
    | exception (Failure(_)) => None
    };
  } else {
    None;
  };

let fromRGB = (red, green, blue) => {
  r: byteToUnit(red),
  g: byteToUnit(green),
  b: byteToUnit(blue),
};

let fromRGBu = (red, green, blue) => {
  r: constrainUnit(red),
  g: constrainUnit(green),
  b: constrainUnit(blue),
};

let fromHexString = hexString =>
  if (hexString |> String.length == 6) {
    let r = String.sub(hexString, 0, 2) |> hexPairToUnit;
    let g = String.sub(hexString, 2, 2) |> hexPairToUnit;
    let b = String.sub(hexString, 4, 2) |> hexPairToUnit;
    switch (r, g, b) {
    | (Some(r), Some(g), Some(b)) => Some({r, g, b})
    | _ => None
    };
  } else {
    None;
  };

let fromHSLuv = (hue, saturation, lightness) => {
  let h = hue *. 360.0;
  let s = saturation *. 100.0;
  let l = lightness *. 100.0;
  let (r, g, b) = HSLuv.hsluvToRgb((h, s, l));
  fromRGBu(r, g, b);
};

let toRGBu = ({r, g, b}: t) => (r, g, b);

let toRGB = ({r, g, b}: t) => (
  unitToByte(r),
  unitToByte(g),
  unitToByte(b),
);

let toHexString = ({r, g, b}: t) =>
  unitToHexString(r) ++ unitToHexString(g) ++ unitToHexString(b);

let toHSLuv = ({r, g, b}) => {
  let (hue, saturation, lightness) = HSLuv.rgbToHsluv((r, g, b));
  let h = hue /. 360.0;
  let s = saturation /. 100.0;
  let l = lightness /. 100.0;
  (h, s, l);
};