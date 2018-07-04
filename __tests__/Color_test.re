open Jest;

open Color;

open Iterator;

open Utils;

let equalColors = [
  ((255, 255, 255), (1.0, 1.0, 1.0), "ffffff", (0.0, 0.0, 1.0)),
  ((0, 0, 0), (0.0, 0.0, 0.0), "000000", (0.0, 0.0, 0.0)),
  ((128, 128, 128), (0.5, 0.5, 0.5), "808080", (0.0, 0.0, 0.536)),
  ((86, 127, 121), (0.33725, 0.498, 0.4745), "567f79", (0.5, 0.5, 0.5)),
  ((188, 86, 110), (0.73725, 0.33725, 0.43137), "bc566e", (1.0, 0.5, 0.5)),
  ((188, 86, 110), (0.73725, 0.33725, 0.43137), "bc566e", (0.0, 0.5, 0.5)),
  /* Demonstrate the limits of rounding: */
  /* If you increment the last digit of the long floats, these will fail. */
  (
    (254, 255, 255),
    (0.9980392156, 1.0, 1.0),
    "feffff",
    (0.5338888889, 1.0, 0.999),
  ),
  (
    (1, 0, 0),
    (0.005882352941, 0.0, 0.0),
    "010000",
    (0.03382514064, 1.0, 0.0005830025691476508),
  ),
  /* If you decrement the last digit of the long floats, these will fail. */
  (
    (254, 255, 255),
    (0.9941177, 1.0, 1.0),
    "feffff",
    (0.5338888889, 1.0, 0.999),
  ),
  (
    (1, 0, 0),
    (0.001960784314, 0.0, 0.0),
    "010000",
    (0.03382514064, 1.0, 0.0005830025691476508),
  ),
];

let invalidHexStrings = [
  "",
  " ",
  "ffffff1",
  "fffffg",
  "f",
  "0",
  "0088f",
  "-ffffff",
];

let validHexStrings = [
  "ffffff",
  "FFFFFF",
  "000000",
  "123456",
  "7890ab",
  "cdefff",
];

let hsluvs = [
  (0.0, 0.0, 0.0),
  (0.5, 0.0, 0.0),
  (1.0, 0.0, 0.0),
  (0.0, 0.5, 0.0),
  (0.0, 1.0, 0.0),
  (0.0, 0.0, 0.5),
  (0.0, 0.0, 1.0),
];

let foo =
  describe(
    "Color",
    ExpectJs.(
      () => {
        describe(
          "colors should be close enough to have the same hex strings", () =>
          equalColors
          |> List.iteri(
               (index, ((r, g, b), (ru, gu, bu), hexString, (h, s, l))) => {
               let rgb = (fromRGB(r, g, b), {j|fromRGB($r, $g, $b)|j});
               let rgbu = (
                 fromRGBu(ru, gu, bu),
                 {j|fromRGBu($ru, $gu, $bu)|j},
               );
               let hex = (
                 fromHexString(hexString) |> optionGet,
                 {j|fromHexString("$hexString")|j},
               );
               let hsluv = (fromHSLuv(h, s, l), {j|fromHSLuv($h, $s, $l)|j});
               let colors = [rgb, rgbu, hex, hsluv];
               let colors = colors |> List.map(((color, _)) => color);
               let hexStrings = colors |> List.map(toHexString);
               let firstHexString = List.hd(hexStrings);
               test({j|$hexString|j}, () =>
                 expect(
                   hexStrings
                   |> List.for_all(hexString => hexString == firstHexString),
                 )
                 |> toBeTruthy
               );
             })
        );
        describe("fromHexString", () => {
          invalidHexStrings
          |> List.iter(hexString =>
               test({j|invalid: "$hexString"|j}, () =>
                 expect(hexString |> fromHexString) |> toEqual(None)
               )
             );
          /* Only.test("foo", () =>
               expect(fromHSLuv(1.0, 0.5, 0.5) |> toHexString)
               |> toEqual("asdf")
             ); */
          validHexStrings
          |> List.iter(hexString =>
               test({j|valid: "$hexString"|j}, () => {
                 let color = hexString |> fromHexString |> optionGet;
                 expect(color |> toHexString)
                 |> toEqual(hexString |> String.lowercase);
               })
             );
        });
        describe(
          "fromHSLuv and toHSLuv are close enough to have the same hex strings",
          () =>
          hsluvs
          |> List.iter(((h, s, l)) => {
               let color = fromHSLuv(h, s, l);
               let (h', s', l') = color |> toHSLuv;
               let color' = fromHSLuv(h', s', l');
               test({j|$h, $s, $l|j}, () =>
                 expect(color' |> toHexString)
                 |> toEqual(color |> toHexString)
               );
             })
        );
      }
    ),
  );