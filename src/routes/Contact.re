let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ()),
      "container":
        style(
          ~alignItems=`flexStart,
          ~justifyContent=`center,
          ~height=100.->pct,
          ~padding=25.->dp,
          (),
        ),
      "txt":
        style(
          ~color="#fff",
          ~fontSize=28.,
          ~paddingTop=20.->dp,
          ~fontWeight=`_600,
          (),
        ),
      "txtArea": style(~backgroundColor="white", ~width=100.->pct, ()),
      "orange":
        style(
          ~color="rgb(223,63,42)",
          ~marginBottom=5.->dp,
          ~fontWeight=`_700,
          ~fontSize=22.,
          (),
        ),
    })
  );

[@react.component]
let make = (~navigation as _, ~route as _) => {
  let (text, setText) = React.useState(() => "");
  let (errorNoWhats, setErrorNoWhats) = React.useState(() => false);
  ReactNative.(
    <View style={styles##bg}>
      <View style={styles##container}>
        <Text style={styles##orange}>
          {j|Conte-nos sua experiência:|j}->React.string
        </Text>
        <TextInput
          multiline=true
          numberOfLines=16
          style={styles##txtArea}
          onChangeText={txt => setText(_ => txt)}
        />
        <TouchableOpacity
          style={ReactNative.Style.style(~alignSelf=`flexEnd, ())}
          onPress={_ => {
            let url = {j|whatsapp://send?text=$text&phone=5583999651707|j};
            Js.Promise.(
              Linking.canOpenURL(url)
              |> then_(can =>
                   can
                     ? Linking.openURL(url) |> then_(() => resolve(true))
                     : reject(raise(Not_found))
                 )
              |> then_(_ => {
                   Js.log("Opened");
                   resolve();
                 })
              |> catch(_ => {
                   setErrorNoWhats(_ => true);
                   resolve();
                 })
            )
            |> ignore;
          }}>
          <Text style={styles##txt}>
            {!errorNoWhats
               ? "Enviar"->React.string : "Instale o whatsapp"->React.string}
          </Text>
        </TouchableOpacity>
      </View>
    </View>
  );
};