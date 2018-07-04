open Jest;

open Color;

open Iterator;

open Utils;

let equalColors = [
  ((255, 255, 255), (1.0, 1.0, 1.0), "ffffff"),
  ((0, 0, 0), (0.0, 0.0, 0.0), "000000"),
  ((128, 128, 128), (0.5, 0.5, 0.5), "808080"),
  /* Demonstrate the limits of rounding: */
  /* If you increment the last digit of the long floats, these will fail. */
  ((254, 255, 255), (0.9980392156, 1.0, 1.0), "feffff"),
  ((1, 0, 0), (0.005882352941, 0.0, 0.0), "010000"),
  /* If you decrement the last digit of the long floats, these will fail. */
  ((254, 255, 255), (0.9941177, 1.0, 1.0), "feffff"),
  ((1, 0, 0), (0.001960784314, 0.0, 0.0), "010000"),
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

let foo =
  describe(
    "Color",
    ExpectJs.(
      () => {
        describe(
          "colors should be close enough to have the same RGB integers", () =>
          equalColors
          |> List.iter((((r, g, b), (ru, gu, bu), hexString)) => {
               let rgb = (fromRGB(r, g, b), {j|fromRGB($r, $g, $b)|j});
               let rgbu = (
                 fromRGBu(ru, gu, bu),
                 {j|fromRGBu($ru, $gu, $bu)|j},
               );
               let hex = (
                 fromHexString(hexString) |> optionGet,
                 {j|fromHexString("$hexString")|j},
               );
               let colors = fromList([rgb, rgbu, hex]);
               combinations2(colors)
               |> each((((aC, aS), (bC, bS))) =>
                    test(bS ++ " == " ++ aS, () =>
                      expect(aC |> toRGB) |> toEqual(bC |> toRGB)
                    )
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
               expect(hexPairToUnit("80") |> optionGet) |> toEqual(0.5)
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
      }
    ),
  );