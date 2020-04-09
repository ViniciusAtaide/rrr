let styles =
  ReactNative.Style.(
    ReactNative.StyleSheet.create({
      "bg": style(~backgroundColor="rgb(36, 37, 36)", ~height=100.->pct, ()),
      "container":
        style(
          ~alignItems=`flexStart,
          ~justifyContent=`spaceBetween,
          ~paddingHorizontal=25.->dp,
          ~paddingVertical=60.->dp,
          ~flex=1.,
          (),
        ),
      "orange":
        style(
          ~color="rgb(254,80,0)",
          ~paddingTop=40.->dp,
          ~fontFamily="Montserrat-Bold",
          ~fontSize=22.,
          (),
        ),
      "center":
        style(
          ~justifyContent=`spaceAround,
          ~alignItems=`center,
          ~width=100.->pct,
          (),
        ),
    })
  );

[@react.component]
let make = (~navigation as _, ~route as _) => {
  ReactNative.(
    <View style={styles##bg}>
      <View style={styles##container}>
        <Text style={styles##orange}>
          {j|Encontre por estado|j}->React.string
        </Text>
      </View>
    </View>
  );
};