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
            ~justifyContent=`center,
            ~height=100.->pct,
            (),
          ),
      })
    )
  );

module Loading = {
  open ReactNative;

  [@react.component]
  let make = () =>
    <View style={styles##center}>
      <Text style={styles##txt}> "Carregando..."->React.string </Text>
    </View>;
};

[@react.component]
let app = () =>
  <ReasonRelay.Context.Provider environment=Relay.environment>
    <React.Suspense fallback={<Loading />}>
      <Router.RootStackScreen />
    </React.Suspense>
  </ReasonRelay.Context.Provider>;