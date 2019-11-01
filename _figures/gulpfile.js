const gulp = require('gulp');
const sass = require('gulp-sass');
const plumber = require('gulp-plumber');
const notify = require('gulp-notify');

const moduleDir = './node_modules/';
const assetsDir = './assets/';

gulp.task('sass', () => {
  return gulp.src(assetsDir + 'scss/**/*.scss')
    .pipe(plumber({
      errorHandler: notify.onError("Error: <%= error.message %>")
    }))
    .pipe(sass({
      outputStyle: 'compressed',
      includePaths: [
        moduleDir + 'ress',
        moduleDir + '@fortawesome/fontawesome-free/scss/'
      ]
    }).on('error', sass.logError))
    // .pipe(autoprefixer({
    //   browsers: ['last 2 versions', 'ie >= 11', 'Android >= 4']
    // }))
    .pipe(gulp.dest(assetsDir + 'css'));
});

gulp.task('sass:watch', () => {
  gulp.watch(assetsDir + 'scss/**/*.scss', gulp.task('sass'));
});

gulp.task('fileCopy', () => {
  gulp.src(moduleDir + '@fortawesome/fontawesome-free/webfonts/*')
  .pipe(gulp.dest(assetsDir + 'webfonts'));
});

gulp.task('default', gulp.series(gulp.parallel('fileCopy', 'sass:watch')));
