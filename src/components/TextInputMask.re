include ReactNative.TextInputElement;

[@bs.module "react-native-text-input-mask"] [@react.component]
external make:
  (
    ~onChangeText: string => unit,
    ~mask: string,
    ~returnKeyType: [@bs.string] [ | `go | `next],
    ~keyboardType: [@bs.string] [
                     | [@bs.as "number-pad"] `numberPad
                     | [@bs.as "phone-pad"] `phonePad
                   ],
    ~style: ReactNative.Style.t=?,
    ~blurOnSubmit: bool=?,
    ~ref: ref=?,
    ~onSubmitEditing: ReactNative.TextInput.editingEvent => unit=?
  ) =>
  React.element =
  "default";