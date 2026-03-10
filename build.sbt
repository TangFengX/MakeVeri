ThisBuild / scalaVersion     := "2.13.12"
ThisBuild / version          := "0.1.0"
ThisBuild / organization     := "%ORGANIZATION%"




lazy val root = (project in file("."))
  .settings(
    name := "%NAME%",
    Compile / scalaSource := baseDirectory.value / "src/chisel/main/scala",
    Test / scalaSource := baseDirectory.value / "src/chisel/test/scala",
    libraryDependencies ++= Seq(
      "org.chipsalliance" %% "chisel" % "6.0.0",
      "edu.berkeley.cs" %% "chiseltest" % "6.0.0" % "test"
    ),
    scalacOptions ++= Seq(
      "-language:reflectiveCalls",
      "-deprecation",
      "-feature",
      "-Xcheckinit",
      "-Ymacro-annotations",
    ),
    addCompilerPlugin("org.chipsalliance" % "chisel-plugin" % "6.0.0" cross CrossVersion.full),
  )