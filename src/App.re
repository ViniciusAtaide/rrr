let styles =
  Colors.(
    ReactNative.Style.(
      ReactNative.StyleSheet.create({
        "scrollView": style(~backgroundColor=colors##lighter, ()),
        "body": style(~backgroundColor=colors##white, ()),
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
      <Text> "Loading"->React.string </Text>
    </View>;
};

[@react.component]
let app = () =>
  <ReasonRelay.Context.Provider environment=Relay.environment>
    <React.Suspense fallback={<Loading />}>
      <Router.RootStackScreen />
    </React.Suspense>
  </ReasonRelay.Context.Provider>;