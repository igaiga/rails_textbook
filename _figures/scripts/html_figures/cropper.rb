# 画像を指示したサイズに切り取り
class Cropper
  def self.width_height(file_path)
    dir_name, file_name = file_path.split("/").last(2)
    wh = {
      "crud" => {
        "crud_4_pages.png" => [1820, 1380],
        "index_flow.png" => [1320, 1000],
        "index_flow_controller.png" => [1320, 1000],
        "index_flow_routes.png" => [1320, 1000],
        "index_flow_view.png" => [1320, 1000],
        "index_routes.png" => [1800, 1020],
      },
      "model" => {
        "create_flow_controller.png" => [1320, 1100],
        "migration_created.png" => [1340, 980],
        "migration_how_to_make_db.png" => [1340, 1200],
        "migration_new_column_author.png" => [1820, 1060],
        "migration_rails_db_migrate.png" => [1320, 1340],
        "summary_model_db.png" => [1820, 1320],
        "summary_rails_db_migrate.png" => [1820, 1320],
        "summary_scaffold_make_files.png" => [1820, 1320],
      },
      "new-create" => {
        "create_flow_controller.png" => [1320, 1100],
        "create_flow_routes.png" => [1320, 1120],
        "create_overview.png" => [1820, 900],
        "create_routes.png" => [1820, 1180],
        "new_flow.png" => [1320, 980],
        "new_flow_controller.png" => [1320, 980],
        "new_flow_routes.png" => [1320, 980],
        "new_flow_view.png" => [1320, 980],
        "new_routes.png" => [1800, 960],
        "new_view_form.png" => [1820, 1140],
        "new_view_form_memo_html.png" => [1820, 740],
        "new_view_form_screenshot.png" => [960, 920],
        "new_view_form_submit_html.png" => [1820, 680],
        "new_view_form_title_html.png" => [1820, 680],
      },
      "smallest-app" => {
        "instance_variable.png" => [1320, 1180],
        "rails_app_request_to_response.png" => [1320, 980],
        "rails_files.png" => [980, 580],
        "rails_g_controller.png" => [1180, 760],
        "routes.png" => [1820, 940],
        "routes_mapping.png" => [1320, 480],
      },
    }
    wh[dir_name][file_name]
  end

  def self.crop
    Dir.glob("tmp/**/*.png") do |file_path|
      width, height = width_height(file_path)
      if width.nil? || height.nil?
        puts "width_heightメソッドに #{file_path} の画像サイズを追加してください"
        next
      end
      puts "#{file_path}: #{width}, #{height}"
      crop_exec(file_path, width, height)
    end
  end

  private_class_method def self.crop_exec(file_path, width, height)
    # imagemagickのconvert機能をつかう
    system "magick #{file_path} -crop #{width}x#{height}+0+0 #{file_path}"
  end
end

#system "rm -rf tmp; cp -r tmp_org tmp" # 実装用 バックアップから復元
#system "cp -r tmp tmp_org" # バックアップ

Cropper.crop
