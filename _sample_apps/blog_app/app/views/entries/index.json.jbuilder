json.array!(@entries) do |entry|
  json.extract! entry, :id, :title, :description, :picture
  json.url entry_url(entry, format: :json)
end
