open ReactNative;
let styles =
  Colors.(
    ReactNative.Style.(
      ReactNative.StyleSheet.create({
        "scrollView": style(~backgroundColor=colors##lighter, ()),
        "body": style(~backgroundColor=colors##white, ()),
        "txt":
          style(
            ~color="#fff",
            ~fontSize=26.,
            ~fontFamily="Montserrat-Regular",
            (),
          ),
        "center":
          style(
            ~alignItems=`center,
            ~backgroundColor="rgb(63,63,63)",
            ~justifyContent=`center,
            ~height=100.->pct,
            (),
          ),
      })
    )
  );
[@react.component]
let make = () =>
  <View style={styles##center}>
    <Text style={styles##txt}> "Carregando..."->React.string </Text>
  </View>;