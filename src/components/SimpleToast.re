type duration;
type gravity;

[@bs.module "react-native-simple-toast"] [@bs.scope "default"]
external show: string => unit = "show";

[@bs.module "react-native-simple-toast"] [@bs.scope "default"]
external showWithGravity: (string, duration, gravity) => unit =
  "showWithGravity";

[@bs.module "react-native-simple-toast"] [@bs.scope "default"]
external short: duration = "SHORT";

[@bs.module "react-native-simple-toast"] [@bs.scope "default"]
external long: duration = "LONG";

[@bs.module "react-native-simple-toast"] [@bs.scope "default"]
external bottom: gravity = "BOTTOM";

[@bs.module "react-native-simple-toast"] [@bs.scope "default"]
external center: gravity = "CENTER";

[@bs.module "react-native-simple-toast"] [@bs.scope "default"]
external top: gravity = "TOP";